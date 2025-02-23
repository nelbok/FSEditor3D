#include <fse/managers/InterfaceManager.hpp>

#include <QtGui/QClipboard>
#include <QtGui/QGuiApplication>

#include <fse/managers/CommandsManager.hpp>
#include <fse/managers/ErrorsManager.hpp>
#include <fse/managers/FileManager.hpp>
#include <fse/managers/UpdateManager.hpp>
#include <fse/Manager.hpp>

/* Process:
AskSaveDialog will call:
- SaveClicked
- DiscardClicked
- CancelClicked

FileDialog will call:
- Either SaveFile / LoadFile
- CancelClicked
*/

namespace fse {
enum class Status {
	None,
	AskResetting,
	AskSaving,
	AskLoading,
	AskQuitting,
	SaveBeforeResetting,
	SaveBeforeLoading,
	SaveBeforeQuitting,
	Saving,
	Loading,
};

struct InterfaceManager::Impl {
	InterfaceManager* parent{ nullptr };
	Manager* manager{ nullptr };
	CommandsManager* commands{ nullptr };
	ErrorsManager* errors{ nullptr };
	FileManager* file{ nullptr };
	UpdateManager* update{ nullptr };
	bool isAskSaveDialogVisible{ false };
	Status status{ Status::None };
	QString message{ "" };

	void processErrors() {
		setMessage(errors->message());
	}

	void processResult() {
		if (file->result() == fsd::FileManager::Result::Success)
			nextStep();
		else
			setStatus(Status::None);
	}

	void processUpdate() {
		setMessage(QObject::tr("A new version is available:\nVersion %1").arg(update->version()));
	}

	void checkSaveNeeded() {
		if (!commands->isModified()) {
			nextStep();
			return;
		}

		switch (status) {
			case Status::AskResetting:
				setStatus(Status::SaveBeforeResetting);
				setIsAskSaveDialogVisible(true);
				break;
			case Status::AskLoading:
				setStatus(Status::SaveBeforeLoading);
				setIsAskSaveDialogVisible(true);
				break;
			case Status::AskQuitting:
				setStatus(Status::SaveBeforeQuitting);
				setIsAskSaveDialogVisible(true);
				break;
			default:
				assert(!"Wrong interface event");
				setStatus(Status::None);
				break;
		}
	}

	void nextStep() {
		switch (status) {
			case Status::AskResetting:
			case Status::SaveBeforeResetting:
				manager->reset();
				setStatus(Status::None);
				break;
			case Status::AskLoading:
			case Status::SaveBeforeLoading:
				emit parent->openLoadDialog();
				break;
			case Status::AskQuitting:
			case Status::SaveBeforeQuitting:
				manager->reset();
				QCoreApplication::quit();
				break;
			case Status::Saving:
			case Status::Loading:
				setStatus(Status::None);
				break;
			default:
				assert(!"Wrong interface event");
				setStatus(Status::None);
				break;
		}
	}

	void setIsAskSaveDialogVisible(bool visible) {
		if (isAskSaveDialogVisible == visible)
			return;
		isAskSaveDialogVisible = visible;
		emit parent->isAskSaveDialogVisibleUpdated();
	}

	void setStatus(Status s) {
		if (status == s)
			return;
		status = s;
		emit parent->isInterfaceEnabledUpdated();
	}

	void setMessage(const QString& m) {
		if (message == m)
			return;
		message = m;
		emit parent->isMessageDialogVisibleUpdated();
		emit parent->isInterfaceEnabledUpdated();
	}
};

InterfaceManager::InterfaceManager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

InterfaceManager::~InterfaceManager() = default;

void InterfaceManager::init(Manager* manager) {
	assert(!_impl->manager);

	_impl->parent = this;
	_impl->manager = manager;
	_impl->commands = manager->commandsManager();
	_impl->errors = manager->errorsManager();
	_impl->file = manager->fileManager();
	_impl->update = manager->updateManager();

	connect(_impl->errors, &ErrorsManager::typeUpdated, this, [this]() {
		_impl->processErrors();
	});
	connect(_impl->file, &FileManager::statusUpdated, this, &InterfaceManager::isProgressDialogVisibleUpdated);
	connect(_impl->file, &FileManager::statusUpdated, this, &InterfaceManager::isInterfaceEnabledUpdated);
	connect(_impl->file, &FileManager::endTransaction, this, [this]() {
		_impl->processResult();
	});
	connect(_impl->update, &UpdateManager::newVersionAvailable, this, [this]() {
		_impl->processUpdate();
	});
}

bool InterfaceManager::isProgressDialogVisible() const {
	switch (_impl->file->status()) {
		using enum FileManager::Status;
		case None:
		case Stopped:
			return false;
		default:
			break;
	}
	return true;
}

bool InterfaceManager::isMessageDialogVisible() const {
	return _impl->message != "";
}

bool InterfaceManager::isAskSaveDialogVisible() const {
	return _impl->isAskSaveDialogVisible;
}

bool InterfaceManager::isInterfaceEnabled() const {
	if (_impl->status != Status::None)
		return false;
	if (isMessageDialogVisible())
		return false;
	if (isProgressDialogVisible())
		return false;
	return true;
}

QString InterfaceManager::message() const {
	return _impl->message;
}

void InterfaceManager::reset() {
	assert(_impl->manager);
	_impl->setStatus(Status::AskResetting);
	_impl->checkSaveNeeded();
}

void InterfaceManager::load() {
	assert(_impl->manager);
	_impl->setStatus(Status::AskLoading);
	_impl->checkSaveNeeded();
}

void InterfaceManager::save() {
	assert(_impl->manager);
	_impl->setStatus(Status::AskSaving);
	emit openSaveDialog();
}

void InterfaceManager::quit() {
	assert(_impl->manager);
	_impl->setStatus(Status::AskQuitting);
	_impl->checkSaveNeeded();
}

void InterfaceManager::requestFileTransactionInterruption() {
	assert(_impl->manager);
	_impl->file->requestFileTransactionInterruption();
}

void InterfaceManager::setClipboardText(const QString& text) const {
	QGuiApplication::clipboard()->setText(text);
}

void InterfaceManager::checkForUpdates() {
	_impl->update->checkForUpdates();
}

void InterfaceManager::okClicked() {
	// Stop showing the message dialog
	_impl->setMessage("");
}

void InterfaceManager::saveClicked() {
	// Open the save dialog, either will call Cancel or saveFile
	_impl->setIsAskSaveDialogVisible(false);
	emit openSaveDialog();
}

void InterfaceManager::discardClicked() {
	// No saving and continue the process
	_impl->setIsAskSaveDialogVisible(false);
	_impl->nextStep();
}

void InterfaceManager::cancelClicked() {
	// End of the process
	_impl->setIsAskSaveDialogVisible(false);
	_impl->setStatus(Status::None);
}

void InterfaceManager::saveFile(const QUrl& url) {
	switch (_impl->status) {
		case Status::AskSaving:
			_impl->setStatus(Status::Saving);
			[[fallthrough]];
		case Status::SaveBeforeResetting:
		case Status::SaveBeforeLoading:
		case Status::SaveBeforeQuitting:
			// Will save and call Impl::processResult
			_impl->file->save(url);
			break;
		default:
			assert(!"Wrong interface event");
			break;
	}
}

void InterfaceManager::loadFile(const QUrl& url) {
	// Will load and call Impl::processResult
	_impl->setStatus(Status::Loading);
	_impl->file->load(url);
}
} // namespace fse

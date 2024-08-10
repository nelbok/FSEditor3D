#include "Manager.hpp"

#include <filesystem>

#include <QtGui/QGuiApplication>
#include <QtGui/QClipboard>

#include "Config.hpp"

#include "managers/CommandsManager.hpp"
#include "managers/ModelsManager.hpp"
#include "managers/SelectionManager.hpp"
#include "managers/StylesManager.hpp"
#include "managers/TranslationsManager.hpp"

#include "tools/LoadThread.hpp"
#include "tools/SaveThread.hpp"

namespace fse {

struct Manager::Impl {
	About about;
	Balsam* balsam{ nullptr };
	fsd::Project* project{ nullptr };

	QUrl tmpPath{};
	QUrl oldPath{};
	QUrl path{};
	fse::FileThread* fileThread{ nullptr };

	CommandsManager* commandsManager{ nullptr };
	ModelsManager* modelsManager{ nullptr };
	SelectionManager* selectionManager{ nullptr };
	StylesManager* stylesManager{ nullptr };
	TranslationsManager* translationsManager{ nullptr };

	template<class T>
	void manageFile(Manager* manager, const QUrl& url) {
		static_assert(std::is_base_of<fse::FileThread, T>::value, "T must inherit from fse::FileThread");
		manager->setPath(url);
		fileThread = new T(manager);
		fileThread->init();
		emit manager->beginFileTransaction();
		manager->connect(fileThread, &T::finished, manager, [this, manager]() {
			emit manager->endFileTransaction(fileThread->result());
			fileThread->deleteLater();
			fileThread = nullptr;
		});
		fileThread->start();
	}
};

Manager::Manager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

Manager::~Manager() {
	reset();
}

void Manager::init() {
	assert(!_impl->project);

	_impl->balsam = new Balsam(this);
	_impl->project = new fsd::Project(this);

	_impl->commandsManager = new CommandsManager(this);
	_impl->modelsManager = new ModelsManager(this);
	_impl->selectionManager = new SelectionManager(this);
	_impl->stylesManager = new StylesManager(this);
	_impl->translationsManager = new TranslationsManager(this);

	_impl->balsam->init(this);

	_impl->commandsManager->init(_impl->project);
	_impl->modelsManager->init(_impl->project);
	_impl->selectionManager->init(_impl->project);
	_impl->stylesManager->init();
	_impl->translationsManager->init();

	reset();
}

void Manager::reset() {
	_impl->project->reset();
	_impl->commandsManager->reset();

	auto tmp = std::filesystem::temp_directory_path();
	tmp /= fsd::Config::name;
	tmp /= _impl->project->uuid().toString(QUuid::WithoutBraces).toStdString();
	tmp /= "";
	_impl->tmpPath = QUrl::fromLocalFile(QString::fromStdString(tmp.string()));
	_impl->oldPath = _impl->tmpPath;
	_impl->path = QUrl();
}

void Manager::load(const QUrl& url) {
	reset();
	_impl->manageFile<fse::LoadThread>(this, url);
}

void Manager::save(const QUrl& url) {
	_impl->manageFile<fse::SaveThread>(this, url);
}

void Manager::requestFileTransactionInterruption() {
	assert(_impl->fileThread);
	_impl->fileThread->requestInterruption();
}

void Manager::setClipboardText(const QString& text) {
	qApp->clipboard()->setText(text);
}

const About& Manager::about() const {
	return _impl->about;
}

Balsam* Manager::balsam() const {
	assert(_impl->balsam);
	return _impl->balsam;
}

fsd::Project* Manager::project() const {
	assert(_impl->project);
	return _impl->project;
}

const QUrl& Manager::tmpPath() const {
	return _impl->tmpPath;
}

const QUrl& Manager::oldPath() const {
	return _impl->oldPath;
}

const QUrl& Manager::path() const {
	return _impl->path;
}

void Manager::setPath(const QUrl& path) {
	if (_impl->path != path || _impl->oldPath != path) {
		if (_impl->path.isValid()) {
			_impl->oldPath = _impl->path;
		}
		_impl->path = path;
		emit pathUpdated();
	}
}

CommandsManager* Manager::commandsManager() const {
	assert(_impl->commandsManager);
	return _impl->commandsManager;
}

ModelsManager* Manager::modelsManager() const {
	assert(_impl->modelsManager);
	return _impl->modelsManager;
}

SelectionManager* Manager::selectionManager() const {
	assert(_impl->selectionManager);
	return _impl->selectionManager;
}

StylesManager* Manager::stylesManager() const {
	assert(_impl->stylesManager);
	return _impl->stylesManager;
}

TranslationsManager* Manager::translationsManager() const {
	assert(_impl->translationsManager);
	return _impl->translationsManager;
}
} // namespace fse

#include <fse/Manager.hpp>

#include <QtGui/QClipboard>
#include <QtGui/QGuiApplication>

#include <fse/managers/CommandsManager.hpp>
#include <fse/managers/ErrorsManager.hpp>
#include <fse/managers/FileManager.hpp>
#include <fse/managers/KeyBindingsManager.hpp>
#include <fse/managers/ModelsManager.hpp>
#include <fse/managers/PreviewManager.hpp>
#include <fse/managers/SelectionManager.hpp>
#include <fse/managers/StylesManager.hpp>
#include <fse/managers/TranslationsManager.hpp>
#include <fse/managers/UpdateManager.hpp>

namespace fse {

struct Manager::Impl {
	About about;
	Balsam* balsam{ nullptr };
	Settings settings;
	fsd::Project* project{ nullptr };

	CommandsManager* commandsManager{ nullptr };
	ErrorsManager* errorsManager{ nullptr };
	FileManager* fileManager{ nullptr };
	KeyBindingsManager* keyboardsManager{ nullptr };
	ModelsManager* modelsManager{ nullptr };
	PreviewManager* previewManager{ nullptr };
	SelectionManager* selectionManager{ nullptr };
	StylesManager* stylesManager{ nullptr };
	TranslationsManager* translationsManager{ nullptr };
	UpdateManager* updateManager{ nullptr };
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
	_impl->errorsManager = new ErrorsManager(this);
	_impl->fileManager = new FileManager(this);
	_impl->keyboardsManager = new KeyBindingsManager(this);
	_impl->modelsManager = new ModelsManager(this);
	_impl->previewManager = new PreviewManager(this);
	_impl->selectionManager = new SelectionManager(this);
	_impl->stylesManager = new StylesManager(this);
	_impl->translationsManager = new TranslationsManager(this);
	_impl->updateManager = new UpdateManager(this);

	_impl->balsam->init(_impl->fileManager, _impl->commandsManager);

	_impl->commandsManager->init(_impl->project);
	_impl->fileManager->init(this);
	_impl->keyboardsManager->init();
	_impl->modelsManager->init(_impl->project);
	_impl->previewManager->init(this);
	_impl->stylesManager->init(_impl->errorsManager);
	_impl->translationsManager->init(_impl->errorsManager);

	// Settings
	_impl->settings.init(this);
	connect(qApp, &QCoreApplication::aboutToQuit, this, [this]() {
		_impl->settings.save();
	});
	_impl->settings.load();

	reset();
}

void Manager::reset() {
	_impl->selectionManager->reset();
	_impl->project->reset();
	_impl->commandsManager->reset();
	_impl->fileManager->reset();
	_impl->previewManager->reset();
}

void Manager::setClipboardText(const QString& text) const {
	QGuiApplication::clipboard()->setText(text);
}

const About& Manager::about() const {
	return _impl->about;
}

Balsam* Manager::balsam() const {
	assert(_impl->balsam);
	return _impl->balsam;
}

const Settings& Manager::settings() const {
	return _impl->settings;
}

fsd::Project* Manager::project() const {
	assert(_impl->project);
	return _impl->project;
}

CommandsManager* Manager::commandsManager() const {
	assert(_impl->commandsManager);
	return _impl->commandsManager;
}

ErrorsManager* Manager::errorsManager() const {
	assert(_impl->errorsManager);
	return _impl->errorsManager;
}

FileManager* Manager::fileManager() const {
	assert(_impl->fileManager);
	return _impl->fileManager;
}

KeyBindingsManager* Manager::keyboardsManager() const {
	assert(_impl->keyboardsManager);
	return _impl->keyboardsManager;
}

ModelsManager* Manager::modelsManager() const {
	assert(_impl->modelsManager);
	return _impl->modelsManager;
}

PreviewManager* Manager::previewManager() const {
	assert(_impl->previewManager);
	return _impl->previewManager;
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

UpdateManager* Manager::updateManager() const {
	assert(_impl->updateManager);
	return _impl->updateManager;
}
} // namespace fse

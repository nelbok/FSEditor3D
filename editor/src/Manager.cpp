#include "Manager.hpp"

#include <QtGui/QGuiApplication>
#include <QtGui/QClipboard>

#include "managers/CommandsManager.hpp"
#include "managers/FileManager.hpp"
#include "managers/ModelsManager.hpp"
#include "managers/PreviewManager.hpp"
#include "managers/SelectionManager.hpp"
#include "managers/StylesManager.hpp"
#include "managers/TranslationsManager.hpp"

namespace fse {

struct Manager::Impl {
	About about;
	Balsam* balsam{ nullptr };
	fsd::Project* project{ nullptr };

	CommandsManager* commandsManager{ nullptr };
	FileManager* fileManager{ nullptr };
	ModelsManager* modelsManager{ nullptr };
	PreviewManager* previewManager{ nullptr };
	SelectionManager* selectionManager{ nullptr };
	StylesManager* stylesManager{ nullptr };
	TranslationsManager* translationsManager{ nullptr };
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
	_impl->fileManager = new FileManager(this);
	_impl->modelsManager = new ModelsManager(this);
	_impl->previewManager = new PreviewManager(this);
	_impl->selectionManager = new SelectionManager(this);
	_impl->stylesManager = new StylesManager(this);
	_impl->translationsManager = new TranslationsManager(this);

	_impl->balsam->init(_impl->fileManager, _impl->commandsManager);

	_impl->commandsManager->init(_impl->project);
	_impl->fileManager->init(this);
	_impl->modelsManager->init(_impl->project);
	_impl->previewManager->init(this);
	_impl->stylesManager->init();
	_impl->translationsManager->init();

	reset();
}

void Manager::reset() {
	_impl->selectionManager->reset();
	_impl->project->reset();
	_impl->commandsManager->reset();
	_impl->fileManager->reset();
	_impl->previewManager->reset();
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

CommandsManager* Manager::commandsManager() const {
	assert(_impl->commandsManager);
	return _impl->commandsManager;
}

FileManager* Manager::fileManager() const {
	assert(_impl->fileManager);
	return _impl->fileManager;
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
} // namespace fse

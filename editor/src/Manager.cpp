#include "Manager.hpp"

#include "CommandsManager.hpp"
#include "ModelsManager.hpp"

namespace lhe {

struct Manager::Impl {
	About* about{ nullptr };
	Balsam* balsam{ nullptr };
	lh::Project* project{ nullptr };

	CommandsManager* commandsManager{ nullptr };
	ModelsManager* modelsManager{ nullptr };
};

Manager::Manager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

Manager::~Manager() {
	reset();
}

void Manager::init() {
	assert(!_impl->project);

	_impl->about = new About(this);
	_impl->balsam = new Balsam(this);
	_impl->project = new lh::Project(this);

	_impl->commandsManager = new CommandsManager(this);
	_impl->modelsManager = new ModelsManager(this);

	_impl->balsam->init(_impl->project);
	_impl->commandsManager->init(_impl->project);
	_impl->modelsManager->init(_impl->project);

	reset();
}

void Manager::reset() {
	_impl->project->reset();
	_impl->commandsManager->reset();
}

void Manager::load(const QUrl& url) {
	reset();
	_impl->project->load(url);
}

void Manager::save(const QUrl& url) {
	_impl->project->save(url);
}

About* Manager::about() const {
	assert(_impl->about);
	return _impl->about;
}

Balsam* Manager::balsam() const {
	assert(_impl->balsam);
	return _impl->balsam;
}

lh::Project* Manager::project() const {
	assert(_impl->project);
	return _impl->project;
}

CommandsManager* Manager::commandsManager() const {
	assert(_impl->commandsManager);
	return _impl->commandsManager;
}

ModelsManager* Manager::modelsManager() const {
	assert(_impl->modelsManager);
	return _impl->modelsManager;
}
} // namespace lhe

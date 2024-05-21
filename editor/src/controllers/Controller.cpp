#include "Controller.hpp"

namespace lhe {

struct Controller::Impl {
	About* about{ nullptr };
	Commands* commands{ nullptr };
	lh::Project* project{ nullptr };

	// commands
	CharacterCommand* characterCommand{ nullptr };
	EntityCommand* entityCommand{ nullptr };
	LinkCommand* linkCommand{ nullptr };
	ModelCommand* modelCommand{ nullptr };
	PlaceCommand* placeCommand{ nullptr };
	PlacementCommand* placementCommand{ nullptr };
	ProjectCommand* projectCommand{ nullptr };

	// models
	CharacterModel* characterModel{ nullptr };
	LinkModel* linkModel{ nullptr };
	ModelModel* modelModel{ nullptr };
	PlaceModel* placeModel{ nullptr };
};

Controller::Controller(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

Controller::~Controller() {
	reset();
}

void Controller::init() {
	assert(!_impl->about);
	assert(!_impl->project);

	_impl->about = new About(this);
	_impl->commands = new Commands(this);
	_impl->project = new lh::Project(this);

	//commands
	_impl->characterCommand = new CharacterCommand(_impl->commands);
	_impl->entityCommand = new EntityCommand(_impl->commands);
	_impl->linkCommand = new LinkCommand(_impl->commands);
	_impl->modelCommand = new ModelCommand(_impl->commands);
	_impl->placeCommand = new PlaceCommand(_impl->commands);
	_impl->placementCommand = new PlacementCommand(_impl->commands);
	_impl->projectCommand = new ProjectCommand(this);

	//models
	_impl->characterModel = new CharacterModel(_impl->project, this);
	_impl->linkModel = new LinkModel(_impl->project, this);
	_impl->modelModel = new ModelModel(_impl->project, this);
	_impl->placeModel = new PlaceModel(_impl->project, this);

	reset();

	// models
	_impl->characterModel->initDatas();
	_impl->linkModel->initDatas();
	_impl->modelModel->initDatas();
	_impl->placeModel->initDatas();
}

void Controller::reset() {
	_impl->project->reset();
	_impl->commands->reset();
}

void Controller::load(const QUrl& url) {
	reset();
	_impl->project->load(url);
}

void Controller::save(const QUrl& url) {
	_impl->project->save(url);
}

About* Controller::about() const {
	assert(_impl->about);
	return _impl->about;
}

Commands* Controller::commands() const {
	assert(_impl->commands);
	return _impl->commands;
}

lh::Project* Controller::project() const {
	assert(_impl->project);
	return _impl->project;
}

// commands

CharacterCommand* Controller::characterCommand() const {
	assert(_impl->characterCommand);
	return _impl->characterCommand;
}

EntityCommand* Controller::entityCommand() const {
	assert(_impl->entityCommand);
	return _impl->entityCommand;
}

LinkCommand* Controller::linkCommand() const {
	assert(_impl->linkCommand);
	return _impl->linkCommand;
}

ModelCommand* Controller::modelCommand() const {
	assert(_impl->modelCommand);
	return _impl->modelCommand;
}

PlaceCommand* Controller::placeCommand() const {
	assert(_impl->placeCommand);
	return _impl->placeCommand;
}

PlacementCommand* Controller::placementCommand() const {
	assert(_impl->placementCommand);
	return _impl->placementCommand;
}

ProjectCommand* Controller::projectCommand() const {
	assert(_impl->projectCommand);
	return _impl->projectCommand;
}

// models

CharacterModel* Controller::characterModel() const {
	assert(_impl->characterModel);
	return _impl->characterModel;
}

LinkModel* Controller::linkModel() const {
	assert(_impl->linkModel);
	return _impl->linkModel;
}

ModelModel* Controller::modelModel() const {
	assert(_impl->modelModel);
	return _impl->modelModel;
}

PlaceModel* Controller::placeModel() const {
	assert(_impl->placeModel);
	return _impl->placeModel;
}
} // namespace lhe

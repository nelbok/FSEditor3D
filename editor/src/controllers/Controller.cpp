#include "Controller.hpp"

namespace lhe {

Controller::Controller(QObject* parent)
	: QObject(parent) {}

Controller::~Controller() {
	reset();
}

void Controller::init() {
	assert(!_about);
	assert(!_project);

	_about = new About(this);
	_commands = new Commands(this);
	_project = new lh::Project(this);

	//commands
	_characterCommand = new CharacterCommand(_commands);
	_entityCommand = new EntityCommand(_commands);
	_linkCommand = new LinkCommand(_commands);
	_modelCommand = new ModelCommand(_commands);
	_placeCommand = new PlaceCommand(_commands);
	_placementCommand = new PlacementCommand(_commands);
	_projectCommand = new ProjectCommand(this);

	//models
	_characterModel = new CharacterModel(_project, this);
	_linkModel = new LinkModel(_project, this);
	_modelModel = new ModelModel(_project, this);
	_placeModel = new PlaceModel(_project, this);

	reset();

	// models
	_characterModel->initDatas();
	_linkModel->initDatas();
	_modelModel->initDatas();
	_placeModel->initDatas();
}

void Controller::reset() {
	_project->reset();
	_commands->reset();
}

void Controller::load(const QUrl& url) {
	reset();
	_project->load(url);
}

void Controller::save(const QUrl& url) {
	_project->save(url);
}

About* Controller::about() const {
	assert(_about);
	return _about;
}

Commands* Controller::commands() const {
	assert(_commands);
	return _commands;
}

lh::Project* Controller::project() const {
	assert(_project);
	return _project;
}

// commands

CharacterCommand* Controller::characterCommand() const {
	assert(_characterCommand);
	return _characterCommand;
}

EntityCommand* Controller::entityCommand() const {
	assert(_entityCommand);
	return _entityCommand;
}

LinkCommand* Controller::linkCommand() const {
	assert(_linkCommand);
	return _linkCommand;
}

ModelCommand* Controller::modelCommand() const {
	assert(_modelCommand);
	return _modelCommand;
}

PlaceCommand* Controller::placeCommand() const {
	assert(_placeCommand);
	return _placeCommand;
}

PlacementCommand* Controller::placementCommand() const {
	assert(_placementCommand);
	return _placementCommand;
}

ProjectCommand* Controller::projectCommand() const {
	assert(_projectCommand);
	return _projectCommand;
}

// models

CharacterModel* Controller::characterModel() const {
	assert(_characterModel);
	return _characterModel;
}

LinkModel* Controller::linkModel() const {
	assert(_linkModel);
	return _linkModel;
}

ModelModel* Controller::modelModel() const {
	assert(_modelModel);
	return _modelModel;
}

PlaceModel* Controller::placeModel() const {
	assert(_placeModel);
	return _placeModel;
}
} // namespace lhe

#include "Controller.hpp"

namespace lhe {

Controller::Controller(QObject* parent)
	: QObject(parent) {}

Controller::~Controller() {}

void Controller::init() {
	assert(!_about);
	assert(!_project);

	_about = new About(this);
	_commands = new Commands(this);
	_project = new lh::Project(this);

	//commands
	_entityCommand = new EntityCommand(_commands);
	_projectCommand = new ProjectCommand(_commands);

	//models
	_characterModel = new CharacterModel(this);
	_linkModel = new LinkModel(this);
	_placeModel = new PlaceModel(this);

	reset();

	// models
	_characterModel->init(_project);
	_linkModel->init(_project);
	_placeModel->init(_project);
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

EntityCommand* Controller::entityCommand() const {
	assert(_entityCommand);
	return _entityCommand;
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

PlaceModel* Controller::placeModel() const {
	assert(_placeModel);
	return _placeModel;
}
} // namespace lhe

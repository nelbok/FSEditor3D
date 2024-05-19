#include "ProjectCommand.hpp"

#include "../Commands.hpp"
#include "../Controller.hpp"
#include "CreateCommand.hpp"
#include "DuplicateCommand.hpp"
#include "RemoveCommand.hpp"
#include "ValueCommand.hpp"

namespace lhe {

ProjectCommand::ProjectCommand(Controller* controller)
	: QObject(controller)
	, _c{ controller }
	, _cm{ controller->commands() }
	, _p{ controller->project() } {
	assert(_cm);
	assert(_p);
}

ProjectCommand::~ProjectCommand() {}

void ProjectCommand::setDefaultPlace(lh::Place* newValue) {
	addValueCommand(_cm, _p, &lh::Project::setDefaultPlace, &lh::Project::defaultPlace, newValue);
}

void ProjectCommand::createCharacter() {
	_cm->add(new CreateCommand<lh::Character>(_p, &lh::Project::createCharacter, &lh::Project::removeCharacter));
}

void ProjectCommand::removeCharacter(lh::Character* character) {
	assert(!character->hasRef());
	_cm->beginList();
	_c->placementCommand()->setPlace(character, nullptr);
	_cm->add(new RemoveCommand<lh::Character>(_p, &lh::Project::removeCharacter, character));
	_cm->endList();
}

void ProjectCommand::duplicateCharacter(lh::Character* character) {
	_cm->add(new DuplicateCommand<lh::Character>(_p, &lh::Project::duplicateCharacter, &lh::Project::removeCharacter, character));
}

void ProjectCommand::createLink() {
	_cm->add(new CreateCommand<lh::Link>(_p, &lh::Project::createLink, &lh::Project::removeLink));
}

void ProjectCommand::removeLink(lh::Link* link) {
	assert(!link->hasRef());
	_cm->beginList();
	_c->placementCommand()->setPlace(link, nullptr);
	_c->linkCommand()->setLink(link, nullptr);
	_cm->add(new RemoveCommand<lh::Link>(_p, &lh::Project::removeLink, link));
	_cm->endList();
}

void ProjectCommand::duplicateLink(lh::Link* link) {
	_cm->add(new DuplicateCommand<lh::Link>(_p, &lh::Project::duplicateLink, &lh::Project::removeLink, link));
}

void ProjectCommand::createModel() {
	_cm->add(new CreateCommand<lh::Model>(_p, &lh::Project::createModel, &lh::Project::removeModel));
}

void ProjectCommand::removeModel(lh::Model* model) {
	assert(!model->hasRef());
	_cm->beginList();
	_cm->add(new RemoveCommand<lh::Model>(_p, &lh::Project::removeModel, model));
	_cm->endList();
}

void ProjectCommand::duplicateModel(lh::Model* model) {
	_cm->add(new DuplicateCommand<lh::Model>(_p, &lh::Project::duplicateModel, &lh::Project::removeModel, model));
}

void ProjectCommand::createPlace() {
	_cm->add(new CreateCommand<lh::Place>(_p, &lh::Project::createPlace, &lh::Project::removePlace));
}

void ProjectCommand::removePlace(lh::Place* place) {
	assert(!place->hasRef());
	_cm->beginList();
	_cm->add(new RemoveCommand<lh::Place>(_p, &lh::Project::removePlace, place));
	_cm->endList();
}

void ProjectCommand::duplicatePlace(lh::Place* place) {
	_cm->add(new DuplicateCommand<lh::Place>(_p, &lh::Project::duplicatePlace, &lh::Project::removePlace, place));
}

} // namespace lhe

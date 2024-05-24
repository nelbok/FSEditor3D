#include "ProjectCommand.hpp"

#include <lh/data/Character.hpp>
#include <lh/data/Link.hpp>
#include <lh/data/Model.hpp>
#include <lh/data/Place.hpp>

#include "../CommandsManager.hpp"
#include "CreateCommand.hpp"
#include "Commands.hpp"
#include "DuplicateCommand.hpp"
#include "LinkCommand.hpp"
#include "PlacementCommand.hpp"
#include "RemoveCommand.hpp"
#include "ValueCommand.hpp"

namespace lhe {

ProjectCommand::ProjectCommand(lh::Project* project, CommandsManager* mng, Commands* commands)
	: QObject(commands)
	, _p{ project }
	, _cm{ mng }
	, _c{ commands } {
	assert(_p);
	assert(_cm);
	assert(_c);
}

ProjectCommand::~ProjectCommand() {}

void ProjectCommand::setDefaultPlace(lh::Place* newValue) {
	addValueCommand(_c, _p, &lh::Project::setDefaultPlace, &lh::Project::defaultPlace, newValue);
}

void ProjectCommand::createCharacter() {
	_c->add(new CreateCommand<lh::Character>(_p, &lh::Project::createCharacter, &lh::Project::removeCharacter));
}

void ProjectCommand::removeCharacter(lh::Character* character) {
	assert(!character->hasRef());
	_c->beginList();
	_cm->placementCommand()->setPlace(character, nullptr);
	_c->add(new RemoveCommand<lh::Character>(_p, &lh::Project::removeCharacter, character));
	_c->endList();
}

void ProjectCommand::duplicateCharacter(lh::Character* character) {
	_c->add(new DuplicateCommand<lh::Character>(_p, &lh::Project::duplicateCharacter, &lh::Project::removeCharacter, character));
}

void ProjectCommand::createLink() {
	_c->add(new CreateCommand<lh::Link>(_p, &lh::Project::createLink, &lh::Project::removeLink));
}

void ProjectCommand::removeLink(lh::Link* link) {
	assert(!link->hasRef());
	_c->beginList();
	_cm->placementCommand()->setPlace(link, nullptr);
	_cm->linkCommand()->setLink(link, nullptr);
	_c->add(new RemoveCommand<lh::Link>(_p, &lh::Project::removeLink, link));
	_c->endList();
}

void ProjectCommand::duplicateLink(lh::Link* link) {
	_c->add(new DuplicateCommand<lh::Link>(_p, &lh::Project::duplicateLink, &lh::Project::removeLink, link));
}

void ProjectCommand::createModel() {
	_c->add(new CreateCommand<lh::Model>(_p, &lh::Project::createModel, &lh::Project::removeModel));
}

void ProjectCommand::removeModel(lh::Model* model) {
	assert(!model->hasRef());
	_c->beginList();
	_c->add(new RemoveCommand<lh::Model>(_p, &lh::Project::removeModel, model));
	_c->endList();
}

void ProjectCommand::duplicateModel(lh::Model* model) {
	_c->add(new DuplicateCommand<lh::Model>(_p, &lh::Project::duplicateModel, &lh::Project::removeModel, model));
}

void ProjectCommand::createPlace() {
	_c->add(new CreateCommand<lh::Place>(_p, &lh::Project::createPlace, &lh::Project::removePlace));
}

void ProjectCommand::removePlace(lh::Place* place) {
	assert(!place->hasRef());
	_c->beginList();
	_c->add(new RemoveCommand<lh::Place>(_p, &lh::Project::removePlace, place));
	_c->endList();
}

void ProjectCommand::duplicatePlace(lh::Place* place) {
	_c->add(new DuplicateCommand<lh::Place>(_p, &lh::Project::duplicatePlace, &lh::Project::removePlace, place));
}

} // namespace lhe

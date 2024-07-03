#include "ProjectCommand.hpp"

#include <fsd/data/Character.hpp>
#include <fsd/data/Link.hpp>
#include <fsd/data/Model.hpp>
#include <fsd/data/Place.hpp>

#include "managers/CommandsManager.hpp"
#include "CreateCommand.hpp"
#include "Commands.hpp"
#include "DuplicateCommand.hpp"
#include "LinkCommand.hpp"
#include "PlacementCommand.hpp"
#include "RemoveCommand.hpp"
#include "ValueCommand.hpp"

namespace fse {

ProjectCommand::ProjectCommand(fsd::Project* project, CommandsManager* mng, Commands* commands)
	: QObject(commands)
	, _p{ project }
	, _cm{ mng }
	, _c{ commands } {
	assert(_p);
	assert(_cm);
	assert(_c);
}

ProjectCommand::~ProjectCommand() {}

void ProjectCommand::setDefaultPlace(fsd::Place* newValue) {
	addValueCommand(_c, _p, &fsd::Project::setDefaultPlace, &fsd::Project::defaultPlace, newValue);
}

void ProjectCommand::createCharacter() {
	_c->add(new CreateCommand<fsd::Character>(_p, &fsd::Project::createCharacter, &fsd::Project::removeCharacter));
}

void ProjectCommand::removeCharacter(fsd::Character* character) {
	assert(!character->hasRef());
	_c->beginList();
	_cm->placementCommand()->setPlace(character, nullptr);
	_c->add(new RemoveCommand<fsd::Character>(_p, &fsd::Project::removeCharacter, character));
	_c->endList();
}

void ProjectCommand::duplicateCharacter(fsd::Character* character) {
	_c->add(new DuplicateCommand<fsd::Character>(_p, &fsd::Project::duplicateCharacter, &fsd::Project::removeCharacter, character));
}

void ProjectCommand::createLink() {
	_c->add(new CreateCommand<fsd::Link>(_p, &fsd::Project::createLink, &fsd::Project::removeLink));
}

void ProjectCommand::removeLink(fsd::Link* link) {
	assert(!link->hasRef());
	_c->beginList();
	_cm->placementCommand()->setPlace(link, nullptr);
	_cm->linkCommand()->setLink(link, nullptr);
	_c->add(new RemoveCommand<fsd::Link>(_p, &fsd::Project::removeLink, link));
	_c->endList();
}

void ProjectCommand::duplicateLink(fsd::Link* link) {
	_c->add(new DuplicateCommand<fsd::Link>(_p, &fsd::Project::duplicateLink, &fsd::Project::removeLink, link));
}

void ProjectCommand::createModel() {
	_c->add(new CreateCommand<fsd::Model>(_p, &fsd::Project::createModel, &fsd::Project::removeModel));
}

void ProjectCommand::removeModel(fsd::Model* model) {
	assert(!model->hasRef());
	_c->beginList();
	_c->add(new RemoveCommand<fsd::Model>(_p, &fsd::Project::removeModel, model));
	_c->endList();
}

void ProjectCommand::duplicateModel(fsd::Model* model) {
	_c->add(new DuplicateCommand<fsd::Model>(_p, &fsd::Project::duplicateModel, &fsd::Project::removeModel, model));
}

void ProjectCommand::createPlace() {
	_c->add(new CreateCommand<fsd::Place>(_p, &fsd::Project::createPlace, &fsd::Project::removePlace));
}

void ProjectCommand::removePlace(fsd::Place* place) {
	assert(!place->hasRef());
	_c->beginList();
	_c->add(new RemoveCommand<fsd::Place>(_p, &fsd::Project::removePlace, place));
	_c->endList();
}

void ProjectCommand::duplicatePlace(fsd::Place* place) {
	_c->add(new DuplicateCommand<fsd::Place>(_p, &fsd::Project::duplicatePlace, &fsd::Project::removePlace, place));
}

} // namespace fse

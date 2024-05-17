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
	, _c{ controller->commands() }
	, _p{ controller->project() } {
	assert(_c);
	assert(_p);
}

ProjectCommand::~ProjectCommand() {}

void ProjectCommand::setDefaultPlace(lh::Place* newValue) {
	addValueCommand(_c, _p, &lh::Project::setDefaultPlace, &lh::Project::defaultPlace, newValue);
}

void ProjectCommand::createCharacter() {
	_c->add(new CreateCommand<lh::Character>(_p, &lh::Project::createCharacter, &lh::Project::removeCharacter));
}

void ProjectCommand::removeCharacter(lh::Character* character) {
	_c->add(new RemoveCommand<lh::Character>(_p, &lh::Project::removeCharacter, character));
}

void ProjectCommand::duplicateCharacter(lh::Character* character) {
	_c->add(new DuplicateCommand<lh::Character>(_p, &lh::Project::duplicateCharacter, &lh::Project::removeCharacter, character));
}

void ProjectCommand::createLink() {
	_c->add(new CreateCommand<lh::Link>(_p, &lh::Project::createLink, &lh::Project::removeLink));
}

void ProjectCommand::removeLink(lh::Link* link) {
	_c->add(new RemoveCommand<lh::Link>(_p, &lh::Project::removeLink, link));
}

void ProjectCommand::duplicateLink(lh::Link* link) {
	_c->add(new DuplicateCommand<lh::Link>(_p, &lh::Project::duplicateLink, &lh::Project::removeLink, link));
}

void ProjectCommand::createPlace() {
	_c->add(new CreateCommand<lh::Place>(_p, &lh::Project::createPlace, &lh::Project::removePlace));
}

void ProjectCommand::removePlace(lh::Place* place) {
	_c->add(new RemoveCommand<lh::Place>(_p, &lh::Project::removePlace, place));
}

void ProjectCommand::duplicatePlace(lh::Place* place) {
	_c->add(new DuplicateCommand<lh::Place>(_p, &lh::Project::duplicatePlace, &lh::Project::removePlace, place));
}

} // namespace lhe

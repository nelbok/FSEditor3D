#include <fse/commands/ProjectCommand.hpp>

#include <fsd/data/Link.hpp>
#include <fsd/data/Model.hpp>
#include <fsd/data/Object.hpp>
#include <fsd/data/Place.hpp>

#include <fse/commands/CreateCommand.hpp>
#include <fse/commands/Commands.hpp>
#include <fse/commands/DuplicateCommand.hpp>
#include <fse/commands/LinkCommand.hpp>
#include <fse/commands/PlacementCommand.hpp>
#include <fse/commands/RemoveCommand.hpp>
#include <fse/commands/ValueCommand.hpp>
#include <fse/managers/CommandsManager.hpp>

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

ProjectCommand::~ProjectCommand() = default;

void ProjectCommand::setDefaultPlace(fsd::Place* newValue) {
	addValueCommand(_c, _p, &fsd::Project::setDefaultPlace, &fsd::Project::defaultPlace, newValue);
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

void ProjectCommand::createObject() {
	_c->add(new CreateCommand<fsd::Object>(_p, &fsd::Project::createObject, &fsd::Project::removeObject));
}

void ProjectCommand::removeObject(fsd::Object* object) {
	assert(!object->hasRef());
	_c->beginList();
	_cm->placementCommand()->setPlace(object, nullptr);
	_c->add(new RemoveCommand<fsd::Object>(_p, &fsd::Project::removeObject, object));
	_c->endList();
}

void ProjectCommand::duplicateObject(fsd::Object* object) {
	_c->add(new DuplicateCommand<fsd::Object>(_p, &fsd::Project::duplicateObject, &fsd::Project::removeObject, object));
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

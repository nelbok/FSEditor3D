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

ProjectCommand::ProjectCommand(fsd::Project* project, CommandsManager* manager, Commands* commands)
	: QObject(commands)
	, _p{ project }
	, _mng{ manager }
	, _cmd{ commands } {
	assert(_p);
	assert(_mng);
	assert(_cmd);
}

ProjectCommand::~ProjectCommand() = default;

void ProjectCommand::setDefaultPlace(fsd::Place* newValue) {
	addValueCommand(_cmd, _p, &fsd::Project::setDefaultPlace, &fsd::Project::defaultPlace, newValue);
}

fsd::Link* ProjectCommand::createLink() {
	auto cmd = new CreateCommand<fsd::Link>(_p, &fsd::Project::createLink, &fsd::Project::removeLink);
	_cmd->add(cmd);
	return cmd->instance();
}

void ProjectCommand::removeLink(fsd::Link* link) {
	assert(!link->hasRef());
	_cmd->beginList();
	_mng->placementCommand()->setPlace(link, nullptr);
	_mng->linkCommand()->setLink(link, nullptr);
	_cmd->add(new RemoveCommand<fsd::Link>(_p, &fsd::Project::removeLink, link));
	_cmd->endList();
}

fsd::Link* ProjectCommand::duplicateLink(fsd::Link* link) {
	auto* cmd = new DuplicateCommand<fsd::Link>(_p, &fsd::Project::duplicateLink, &fsd::Project::removeLink, link);
	_cmd->add(cmd);
	return cmd->instance();
}

fsd::Object* ProjectCommand::createObject() {
	auto* cmd = new CreateCommand<fsd::Object>(_p, &fsd::Project::createObject, &fsd::Project::removeObject);
	_cmd->add(cmd);
	return cmd->instance();
}

void ProjectCommand::removeObject(fsd::Object* object) {
	assert(!object->hasRef());
	_cmd->beginList();
	_mng->placementCommand()->setPlace(object, nullptr);
	_cmd->add(new RemoveCommand<fsd::Object>(_p, &fsd::Project::removeObject, object));
	_cmd->endList();
}

fsd::Object* ProjectCommand::duplicateObject(fsd::Object* object) {
	auto* cmd = new DuplicateCommand<fsd::Object>(_p, &fsd::Project::duplicateObject, &fsd::Project::removeObject, object);
	_cmd->add(cmd);
	return cmd->instance();
}

fsd::Model* ProjectCommand::createModel() {
	auto* cmd = new CreateCommand<fsd::Model>(_p, &fsd::Project::createModel, &fsd::Project::removeModel);
	_cmd->add(cmd);
	return cmd->instance();
}

void ProjectCommand::removeModel(fsd::Model* model) {
	assert(!model->hasRef());
	_cmd->beginList();
	_cmd->add(new RemoveCommand<fsd::Model>(_p, &fsd::Project::removeModel, model));
	_cmd->endList();
}

fsd::Model* ProjectCommand::duplicateModel(fsd::Model* model) {
	auto* cmd = new DuplicateCommand<fsd::Model>(_p, &fsd::Project::duplicateModel, &fsd::Project::removeModel, model);
	_cmd->add(cmd);
	return cmd->instance();
}

fsd::Place* ProjectCommand::createPlace() {
	auto* cmd = new CreateCommand<fsd::Place>(_p, &fsd::Project::createPlace, &fsd::Project::removePlace);
	_cmd->add(cmd);
	return cmd->instance();
}

void ProjectCommand::removePlace(fsd::Place* place) {
	assert(!place->hasRef());
	_cmd->beginList();
	_cmd->add(new RemoveCommand<fsd::Place>(_p, &fsd::Project::removePlace, place));
	_cmd->endList();
}

fsd::Place* ProjectCommand::duplicatePlace(fsd::Place* place) {
	auto* cmd = new DuplicateCommand<fsd::Place>(_p, &fsd::Project::duplicatePlace, &fsd::Project::removePlace, place);
	_cmd->add(cmd);
	return cmd->instance();
}

} // namespace fse

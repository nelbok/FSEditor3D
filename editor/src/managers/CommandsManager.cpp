#include <fse/managers/CommandsManager.hpp>

#include <fse/commands/Commands.hpp>

namespace fse {
struct CommandsManager::Impl {
	Commands* commands{ nullptr };
	EntityCommand* entityCommand{ nullptr };
	GeometryCommand* geometryCommand{ nullptr };
	LinkCommand* linkCommand{ nullptr };
	ModelCommand* modelCommand{ nullptr };
	ObjectCommand* objectCommand{ nullptr };
	PlaceCommand* placeCommand{ nullptr };
	PlacementCommand* placementCommand{ nullptr };
	ProjectCommand* projectCommand{ nullptr };
	ShapeCommand* shapeCommand{ nullptr };

	void* lastCommandSaved{ nullptr };
};

CommandsManager::CommandsManager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

CommandsManager::~CommandsManager() {
	reset();
}

void CommandsManager::init(fsd::Project* project) {
	assert(project);

	_impl->commands = new Commands(this);
	QObject::connect(_impl->commands, &Commands::updated, this, &CommandsManager::updated);

	//commands
	_impl->entityCommand = new EntityCommand(_impl->commands);
	_impl->geometryCommand = new GeometryCommand(_impl->commands);
	_impl->linkCommand = new LinkCommand(_impl->commands);
	_impl->modelCommand = new ModelCommand(_impl->commands);
	_impl->objectCommand = new ObjectCommand(_impl->commands);
	_impl->placeCommand = new PlaceCommand(_impl->commands);
	_impl->placementCommand = new PlacementCommand(_impl->commands);
	_impl->projectCommand = new ProjectCommand(project, this, _impl->commands);
	_impl->shapeCommand = new ShapeCommand(_impl->commands);

	reset();
}

void CommandsManager::reset() {
	_impl->commands->reset();
	_impl->lastCommandSaved = nullptr;
}

bool CommandsManager::canUndo() const {
	return _impl->commands->canUndo();
}

bool CommandsManager::canRedo() const {
	return _impl->commands->canRedo();
}

void CommandsManager::undo() {
	_impl->commands->undo();
}

void CommandsManager::redo() {
	_impl->commands->redo();
}

bool CommandsManager::isModified() const {
	return _impl->lastCommandSaved != _impl->commands->lastCommandDone();
}

void CommandsManager::setIsModified(bool isModified) {
	if (this->isModified() != isModified) {
		_impl->lastCommandSaved = (!isModified) ? _impl->commands->lastCommandDone() : nullptr;
		emit updated();
	}
}

EntityCommand* CommandsManager::entityCommand() const {
	assert(_impl->entityCommand);
	return _impl->entityCommand;
}

GeometryCommand* CommandsManager::geometryCommand() const {
	assert(_impl->geometryCommand);
	return _impl->geometryCommand;
}

LinkCommand* CommandsManager::linkCommand() const {
	assert(_impl->linkCommand);
	return _impl->linkCommand;
}

ModelCommand* CommandsManager::modelCommand() const {
	assert(_impl->modelCommand);
	return _impl->modelCommand;
}

ObjectCommand* CommandsManager::objectCommand() const {
	assert(_impl->objectCommand);
	return _impl->objectCommand;
}

PlaceCommand* CommandsManager::placeCommand() const {
	assert(_impl->placeCommand);
	return _impl->placeCommand;
}

PlacementCommand* CommandsManager::placementCommand() const {
	assert(_impl->placementCommand);
	return _impl->placementCommand;
}

ProjectCommand* CommandsManager::projectCommand() const {
	assert(_impl->projectCommand);
	return _impl->projectCommand;
}

ShapeCommand* CommandsManager::shapeCommand() const {
	assert(_impl->shapeCommand);
	return _impl->shapeCommand;
}
} // namespace fse

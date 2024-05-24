#include "CommandsManager.hpp"

#include "commands/Commands.hpp"

namespace lhe {
struct CommandsManager::Impl {
	Commands* commands{ nullptr };
	CharacterCommand* characterCommand{ nullptr };
	EntityCommand* entityCommand{ nullptr };
	LinkCommand* linkCommand{ nullptr };
	ModelCommand* modelCommand{ nullptr };
	PlaceCommand* placeCommand{ nullptr };
	PlacementCommand* placementCommand{ nullptr };
	ProjectCommand* projectCommand{ nullptr };
};

CommandsManager::CommandsManager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

CommandsManager::~CommandsManager() {
	reset();
}

void CommandsManager::init(lh::Project* project) {
	assert(project);

	_impl->commands = new Commands(this);
	connect(_impl->commands, &Commands::updated, this, &CommandsManager::updated);

	//commands
	_impl->characterCommand = new CharacterCommand(_impl->commands);
	_impl->entityCommand = new EntityCommand(_impl->commands);
	_impl->linkCommand = new LinkCommand(_impl->commands);
	_impl->modelCommand = new ModelCommand(_impl->commands);
	_impl->placeCommand = new PlaceCommand(_impl->commands);
	_impl->placementCommand = new PlacementCommand(_impl->commands);
	_impl->projectCommand = new ProjectCommand(project, this, _impl->commands);

	reset();
}

void CommandsManager::reset() {
	_impl->commands->reset();
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

CharacterCommand* CommandsManager::characterCommand() const {
	assert(_impl->characterCommand);
	return _impl->characterCommand;
}

EntityCommand* CommandsManager::entityCommand() const {
	assert(_impl->entityCommand);
	return _impl->entityCommand;
}

LinkCommand* CommandsManager::linkCommand() const {
	assert(_impl->linkCommand);
	return _impl->linkCommand;
}

ModelCommand* CommandsManager::modelCommand() const {
	assert(_impl->modelCommand);
	return _impl->modelCommand;
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
} // namespace lhe

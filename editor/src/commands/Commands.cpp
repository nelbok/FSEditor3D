#include <fse/commands/Commands.hpp>

#include <fse/commands/BaseCommand.hpp>

namespace fse {

class ListCommand : public BaseCommand {
public:
	using BaseCommand::BaseCommand;
	~ListCommand() override = default;

	void add(BaseCommand* command) {
		_commands.push_back(command);
	}

	bool isEmpty() const {
		return _commands.isEmpty();
	}

	void undo() override {
		std::for_each(_commands.rbegin(), _commands.rend(), [](BaseCommand* command) {
			command->undo();
		});
	}

	void redo() override {
		std::for_each(_commands.begin(), _commands.end(), [](BaseCommand* command) {
			command->redo();
		});
	}

	void finalize() override {
		std::for_each(_commands.begin(), _commands.end(), [](BaseCommand* command) {
			command->finalize();
		});
	}

	void clean() override {
		std::for_each(_commands.rbegin(), _commands.rend(), [](BaseCommand* command) {
			command->clean();
		});
	}

private:
	QList<BaseCommand*> _commands{};
};

Commands::Commands(QObject* parent)
	: QObject(parent) {}

void Commands::add(BaseCommand* command) {
	command->redo();

	// List
	if (!_list.isEmpty()) {
		command->setParent(_list.last());
		_list.last()->add(command);
		return;
	}

	// Normal way
	internalAdd(command);
}

BaseCommand* Commands::lastCommandDone() const {
	if (_undoCommands.isEmpty()) {
		return nullptr;
	}
	return _undoCommands.last();
}

bool Commands::canUndo() const {
	return !_undoCommands.isEmpty();
}
bool Commands::canRedo() const {
	return !_redoCommands.isEmpty();
}

void Commands::undo() {
	assert(!_undoCommands.isEmpty());
	auto* command = _undoCommands.takeLast();
	command->undo();
	_redoCommands.push_back(command);
	emit updated();
}

void Commands::redo() {
	assert(!_redoCommands.isEmpty());
	auto* command = _redoCommands.takeLast();
	command->redo();
	_undoCommands.push_back(command);
	emit updated();
}

void Commands::beginList() {
	_list.append(new ListCommand);
}

void Commands::endList() {
	assert(!_list.last()->isEmpty());
	assert(!_list.isEmpty());
	auto* command = _list.takeLast();
	if (_list.isEmpty()) {
		internalAdd(command);
	} else {
		command->setParent(_list.last());
		_list.last()->add(command);
	}
}

void Commands::reset() {
	clear(_undoCommands);
	clear(_redoCommands);
	emit updated();
}

// FIXME with preferences
constexpr qsizetype maxCommands = 20;

void Commands::internalAdd(BaseCommand* command) {
	command->setParent(this);
	_undoCommands.push_back(command);

	// Clean undo commands
	if (_undoCommands.count() > maxCommands) {
		auto* undoCommand = _undoCommands.takeFirst();
		undoCommand->finalize();
		undoCommand->deleteLater();
	}

	// Clean redo commands
	for (auto* redoCommand : _redoCommands) {
		redoCommand->clean();
	}
	clear(_redoCommands);

	emit updated();
}

void Commands::clear(QList<BaseCommand*>& commands) const {
	for (auto* command : commands) {
		command->deleteLater();
	}
	commands.clear();
}

} // namespace fse

#pragma once

#include <fsd/data/Project.hpp>

#include <fse/commands/BaseCommand.hpp>

namespace fse {
template<typename TClass>
class RemoveCommand : public BaseCommand {
public:
	using RemoveFunc = void (fsd::Project::*)(TClass*);

	RemoveCommand(fsd::Project* project, RemoveFunc remove, TClass* instance)
		: _project{ project }
		, _remove{ remove }
		, _instance{ instance } {
		assert(_project);
		assert(_remove);
		assert(_instance);
	}

	virtual ~RemoveCommand() = default;

	virtual void undo() override {
		assert(!_instance->isAlive());
		_instance->setIsAlive(true);
	}

	virtual void redo() override {
		assert(_instance->isAlive());
		_instance->setIsAlive(false);
	}

	virtual void finalize() override {
		(_project->*_remove)(_instance);
		_instance = nullptr;
	}

private:
	fsd::Project* _project{ nullptr };
	RemoveFunc _remove{ nullptr };
	TClass* _instance{ nullptr };
};
} // namespace fse

#pragma once

#include <lh/data/Project.hpp>

#include "BaseCommand.hpp"

namespace lhe {
template<typename TClass>
class CreateCommand : public BaseCommand {
public:
	using CreateFunc = TClass* (lh::Project::*) ();
	using RemoveFunc = void (lh::Project::*)(TClass*);

	CreateCommand(lh::Project* project, CreateFunc create, RemoveFunc remove)
		: _project{ project }
		, _create{ create }
		, _remove{ remove } {
		assert(_project);
		assert(_create);
		assert(_remove);
	}

	virtual ~CreateCommand() = default;

	virtual void undo() override {
		assert(_instance->isAlive());
		_instance->setIsAlive(false);
	}

	virtual void redo() override {
		if (_instance) {
			assert(!_instance->isAlive());
			_instance->setIsAlive(true);
		} else {
			_instance = (_project->*_create)();
		}
	}

	virtual void clean() override {
		(_project->*_remove)(_instance);
		_instance = nullptr;
	}

private:
	lh::Project* _project{ nullptr };
	CreateFunc _create{ nullptr };
	RemoveFunc _remove{ nullptr };
	TClass* _instance{ nullptr };
};
} // namespace lhe

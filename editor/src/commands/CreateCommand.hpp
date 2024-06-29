#pragma once

#include <fsd/data/Project.hpp>

#include "BaseCommand.hpp"

namespace fse {
template<typename TClass>
class CreateCommand : public BaseCommand {
public:
	using CreateFunc = TClass* (fsd::Project::*) ();
	using RemoveFunc = void (fsd::Project::*)(TClass*);

	CreateCommand(fsd::Project* project, CreateFunc create, RemoveFunc remove)
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
	fsd::Project* _project{ nullptr };
	CreateFunc _create{ nullptr };
	RemoveFunc _remove{ nullptr };
	TClass* _instance{ nullptr };
};
} // namespace fse

#pragma once

#include <lh/data/Project.hpp>

#include "BaseCommand.hpp"

namespace lhe {
template<typename TClass>
class DuplicateCommand : public BaseCommand {
public:
	using DuplicateFunc = TClass* (lh::Project::*) (TClass*);
	using RemoveFunc = void (lh::Project::*)(TClass*);

	DuplicateCommand(lh::Project* project, DuplicateFunc duplicate, RemoveFunc remove, TClass* pattern)
		: _project{ project }
		, _duplicate{ duplicate }
		, _remove{ remove }
		, _pattern{ pattern } {
		assert(_project);
		assert(_duplicate);
		assert(_remove);
		assert(_pattern);
	}

	virtual ~DuplicateCommand() = default;

	virtual void undo() override {
		assert(_instance->isAlive());
		_instance->setIsAlive(false);
	}

	virtual void redo() override {
		if (_instance) {
			assert(!_instance->isAlive());
			_instance->setIsAlive(true);
		} else {
			_instance = (_project->*_duplicate)(_pattern);
		}
	}

	virtual void clean() override {
		(_project->*_remove)(_instance);
		_instance = nullptr;
	}

private:
	lh::Project* _project{ nullptr };
	DuplicateFunc _duplicate{ nullptr };
	RemoveFunc _remove{ nullptr };
	TClass* _pattern{ nullptr };
	TClass* _instance{ nullptr };
};
} // namespace lhe

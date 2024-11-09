#pragma once

#include <fsd/data/Project.hpp>

#include <fse/commands/BaseCommand.hpp>

namespace fse {
template<typename TClass>
class DuplicateCommand : public BaseCommand {
public:
	using DuplicateFunc = TClass* (fsd::Project::*) (TClass*);
	using RemoveFunc = void (fsd::Project::*)(TClass*);

	DuplicateCommand(fsd::Project* project, DuplicateFunc duplicate, RemoveFunc remove, TClass* pattern)
		: _project{ project }
		, _duplicate{ duplicate }
		, _remove{ remove }
		, _pattern{ pattern } {
		assert(_project);
		assert(_duplicate);
		assert(_remove);
		assert(_pattern);
	}

	~DuplicateCommand() override = default;

	void undo() override {
		assert(_instance->isAlive());
		_instance->setIsAlive(false);
	}

	void redo() override {
		if (_instance) {
			assert(!_instance->isAlive());
			_instance->setIsAlive(true);
		} else {
			_instance = (_project->*_duplicate)(_pattern);
		}
	}

	void clean() override {
		(_project->*_remove)(_instance);
		_instance = nullptr;
	}

private:
	fsd::Project* _project{ nullptr };
	DuplicateFunc _duplicate{ nullptr };
	RemoveFunc _remove{ nullptr };
	TClass* _pattern{ nullptr };
	TClass* _instance{ nullptr };
};
} // namespace fse

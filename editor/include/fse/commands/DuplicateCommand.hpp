#pragma once

#include <fsd/data/Container.hpp>

#include <fse/commands/BaseCommand.hpp>

namespace fse {
template<typename TClass>
class DuplicateCommand : public BaseCommand {
public:
	DuplicateCommand(fsd::Container<TClass>* datas, TClass* pattern)
		: _datas{ datas }
		, _pattern{ pattern } {
		assert(_datas);
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
			_instance = _datas->duplicate(_pattern);
		}
	}

	void clean() override {
		_datas->remove(_instance);
		_instance = nullptr;
	}

	TClass* instance() const {
		return _instance;
	}

private:
	fsd::Container<TClass>* _datas{ nullptr };
	TClass* _pattern{ nullptr };
	TClass* _instance{ nullptr };
};
} // namespace fse

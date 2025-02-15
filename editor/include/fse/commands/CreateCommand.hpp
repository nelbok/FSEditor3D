#pragma once

#include <fsd/data/Container.hpp>

#include <fse/commands/BaseCommand.hpp>

namespace fse {
template<typename TClass>
class CreateCommand : public BaseCommand {
public:
	explicit CreateCommand(fsd::Container<TClass>* datas)
		: _datas{ datas } {
		assert(_datas);
	}

	~CreateCommand() override = default;

	void undo() override {
		assert(_instance->isAlive());
		_instance->setIsAlive(false);
	}

	void redo() override {
		if (_instance) {
			assert(!_instance->isAlive());
			_instance->setIsAlive(true);
		} else {
			_instance = _datas->create();
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
	TClass* _instance{ nullptr };
};
} // namespace fse

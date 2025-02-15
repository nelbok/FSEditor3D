#pragma once

#include <fsd/data/Container.hpp>

#include <fse/commands/BaseCommand.hpp>

namespace fse {
template<typename TClass>
class RemoveCommand : public BaseCommand {
public:
	RemoveCommand(fsd::Container<TClass>* datas, TClass* instance)
		: _datas{ datas }
		, _instance{ instance } {
		assert(_datas);
		assert(_instance);
	}

	~RemoveCommand() override = default;

	void undo() override {
		assert(!_instance->isAlive());
		_instance->setIsAlive(true);
	}

	void redo() override {
		assert(_instance->isAlive());
		_instance->setIsAlive(false);
	}

	void finalize() override {
		_datas->remove(_instance);
		_instance = nullptr;
	}

private:
	fsd::Container<TClass>* _datas{ nullptr };
	TClass* _instance{ nullptr };
};
} // namespace fse

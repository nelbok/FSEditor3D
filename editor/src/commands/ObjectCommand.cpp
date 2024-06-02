#include "ObjectCommand.hpp"

#include "Commands.hpp"
#include "ValueCommand.hpp"

namespace lhe {

ObjectCommand::ObjectCommand(Commands* commands)
	: QObject(commands)
	, _c{ commands } {
	assert(commands);
}

ObjectCommand::~ObjectCommand() {}

void ObjectCommand::setModel(lh::Object* o, lh::Model* newValue) {
	addValueCommand(_c, o, &lh::Object::setModel, &lh::Object::model, newValue);
}

} // namespace lhe

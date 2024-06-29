#include "ObjectCommand.hpp"

#include "Commands.hpp"
#include "ValueCommand.hpp"

namespace fse {

ObjectCommand::ObjectCommand(Commands* commands)
	: QObject(commands)
	, _c{ commands } {
	assert(commands);
}

ObjectCommand::~ObjectCommand() {}

void ObjectCommand::setModel(fsd::Object* o, fsd::Model* newValue) {
	addValueCommand(_c, o, &fsd::Object::setModel, &fsd::Object::model, newValue);
}

} // namespace fse

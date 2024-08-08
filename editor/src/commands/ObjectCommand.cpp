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

} // namespace fse

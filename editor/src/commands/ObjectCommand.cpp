#include <fse/commands/ObjectCommand.hpp>

#include <fse/commands/Commands.hpp>
#include <fse/commands/ValueCommand.hpp>

namespace fse {

ObjectCommand::ObjectCommand(Commands* commands)
	: QObject(commands)
	, _c{ commands } {
	assert(commands);
}

ObjectCommand::~ObjectCommand() {}

} // namespace fse

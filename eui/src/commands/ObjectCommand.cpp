#include <fse/commands/ObjectCommand.hpp>

#include <fse/commands/Commands.hpp>
#include <fse/commands/ValueCommand.hpp>

namespace fse {

ObjectCommand::ObjectCommand(Commands* commands)
	: QObject(commands)
	, _cmd{ commands } {
	assert(commands);
}

ObjectCommand::~ObjectCommand() = default;

} // namespace fse

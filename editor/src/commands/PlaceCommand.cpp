#include <fse/commands/PlaceCommand.hpp>

#include <fse/commands/Commands.hpp>
#include <fse/commands/ValueCommand.hpp>

namespace fse {

PlaceCommand::PlaceCommand(Commands* commands)
	: QObject(commands)
	, _c{ commands } {
	assert(commands);
}

PlaceCommand::~PlaceCommand() = default;

} // namespace fse

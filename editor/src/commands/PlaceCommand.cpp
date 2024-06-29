#include "PlaceCommand.hpp"

#include "Commands.hpp"
#include "ValueCommand.hpp"

namespace fse {

PlaceCommand::PlaceCommand(Commands* commands)
	: QObject(commands)
	, _c{ commands } {
	assert(commands);
}

PlaceCommand::~PlaceCommand() {}

} // namespace fse

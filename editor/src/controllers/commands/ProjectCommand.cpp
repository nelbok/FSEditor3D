#include "ProjectCommand.hpp"

#include "../Commands.hpp"
#include "ValueCommand.hpp"

namespace lhe {

ProjectCommand::ProjectCommand(Commands* commands)
	: QObject(commands)
	, _c{ commands } {
	assert(commands);
}

ProjectCommand ::~ProjectCommand() {}

} // namespace lhe

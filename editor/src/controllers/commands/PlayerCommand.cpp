#include "PlayerCommand.hpp"

#include "../Commands.hpp"
#include "ValueCommand.hpp"

namespace lhe {

PlayerCommand::PlayerCommand(Commands* commands)
	: QObject(commands)
	, _c{ commands } {
	assert(commands);
}

PlayerCommand::~PlayerCommand() {}

} // namespace lhe

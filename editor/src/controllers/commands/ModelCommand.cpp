#include "ModelCommand.hpp"

#include "../Commands.hpp"
#include "ValueCommand.hpp"

namespace lhe {

ModelCommand::ModelCommand(Commands* commands)
	: QObject(commands)
	, _c{ commands } {
	assert(commands);
}

ModelCommand::~ModelCommand() {}

} // namespace lhe

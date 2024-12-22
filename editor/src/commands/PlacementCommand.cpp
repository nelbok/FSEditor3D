#include <fse/commands/PlacementCommand.hpp>

#include <fse/commands/Commands.hpp>
#include <fse/commands/ValueCommand.hpp>

namespace fse {

PlacementCommand::PlacementCommand(Commands* commands)
	: QObject(commands)
	, _cmd{ commands } {
	assert(commands);
}

PlacementCommand::~PlacementCommand() = default;

void PlacementCommand::setPlace(fsd::Placement* p, fsd::Place* newValue) {
	addValueCommand(_cmd, p, &fsd::Placement::setPlace, &fsd::Placement::place, newValue);
}

} // namespace fse

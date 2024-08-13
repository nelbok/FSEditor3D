#include "PlacementCommand.hpp"

#include "Commands.hpp"
#include "ValueCommand.hpp"

namespace fse {

PlacementCommand::PlacementCommand(Commands* commands)
	: QObject(commands)
	, _c{ commands } {
	assert(commands);
}

PlacementCommand::~PlacementCommand() {}

void PlacementCommand::setPlace(fsd::Placement* p, fsd::Place* newValue) {
	addValueCommand(_c, p, &fsd::Placement::setPlace, &fsd::Placement::place, newValue);
}

} // namespace fse

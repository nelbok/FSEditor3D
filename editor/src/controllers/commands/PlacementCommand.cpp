#include "PlacementCommand.hpp"

#include "../Commands.hpp"
#include "ValueCommand.hpp"

namespace lhe {

PlacementCommand::PlacementCommand(Commands* commands)
	: QObject(commands)
	, _c{ commands } {
	assert(commands);
}

PlacementCommand::~PlacementCommand() {}

void PlacementCommand::setPosition(lh::Placement* p, const QVector3D& newValue) {
	addValueCommand(_c, p, &lh::Placement::setPosition, &lh::Placement::position, newValue);
}

void PlacementCommand::setRotation(lh::Placement* p, const QVector3D& newValue) {
	addValueCommand(_c, p, &lh::Placement::setRotation, &lh::Placement::rotation, newValue);
}

void PlacementCommand::setPlace(lh::Placement* p, lh::Place* newValue) {
	addValueCommand(_c, p, &lh::Placement::setPlace, &lh::Placement::place, newValue);
}

} // namespace lhe

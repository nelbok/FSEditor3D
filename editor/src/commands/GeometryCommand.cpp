#include "GeometryCommand.hpp"

#include "Commands.hpp"
#include "ValueCommand.hpp"

namespace fse {

GeometryCommand::GeometryCommand(Commands* commands)
	: QObject(commands)
	, _c{ commands } {
	assert(commands);
}

GeometryCommand::~GeometryCommand() {}

void GeometryCommand::setPosition(fsd::Geometry* g, const QVector3D& newValue) {
	addValueCommand(_c, g, &fsd::Geometry::setPosition, &fsd::Geometry::position, newValue);
}

void GeometryCommand::setRotation(fsd::Geometry* g, const QVector3D& newValue) {
	addValueCommand(_c, g, &fsd::Geometry::setRotation, &fsd::Geometry::rotation, newValue);
}

void GeometryCommand::setScale(fsd::Geometry* g, const QVector3D& newValue) {
	addValueCommand(_c, g, &fsd::Geometry::setScale, &fsd::Geometry::scale, newValue);
}

} // namespace fse

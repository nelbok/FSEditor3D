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

void GeometryCommand::setLocalPosition(fsd::Geometry* g, const QVector3D& newValue) {
	addValueCommand(_c, g, &fsd::Geometry::setLocalPosition, &fsd::Geometry::localPosition, newValue);
}

void GeometryCommand::setLocalRotation(fsd::Geometry* g, const QVector3D& newValue) {
	addValueCommand(_c, g, &fsd::Geometry::setLocalRotation, &fsd::Geometry::localRotation, newValue);
}

void GeometryCommand::setLocalScale(fsd::Geometry* g, const QVector3D& newValue) {
	addValueCommand(_c, g, &fsd::Geometry::setLocalScale, &fsd::Geometry::localScale, newValue);
}

} // namespace fse

#pragma once

#include <QtCore/QObject>

#include <fsd/data/Geometry.hpp>

namespace fse {
class Commands;

class GeometryCommand : public QObject {
	Q_OBJECT

public:
	GeometryCommand(Commands* commands);
	virtual ~GeometryCommand();

	Q_INVOKABLE void setPosition(fsd::Geometry* geometry, const QVector3D& position);
	Q_INVOKABLE void setRotation(fsd::Geometry* geometry, const QVector3D& rotation);
	Q_INVOKABLE void setScale(fsd::Geometry* geometry, const QVector3D& scale);

protected:
	Commands* _c{ nullptr };
};
} // namespace fse

#pragma once

#include <QtCore/QObject>

#include <fsd/data/Geometry.hpp>

namespace fse {
class Commands;

class GeometryCommand : public QObject {
	Q_OBJECT

public:
	explicit GeometryCommand(Commands* commands);
	~GeometryCommand() override;

	Q_INVOKABLE void setLocalPosition(fsd::Geometry* geometry, const QVector3D& localPosition);
	Q_INVOKABLE void setLocalRotation(fsd::Geometry* geometry, const QVector3D& localRotation);
	Q_INVOKABLE void setLocalScale(fsd::Geometry* geometry, const QVector3D& localScale);

private:
	Commands* _cmd{ nullptr };
};
} // namespace fse

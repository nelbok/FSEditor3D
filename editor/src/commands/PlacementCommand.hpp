#pragma once

#include <QtCore/QObject>

#include <fsd/data/Placement.hpp>

namespace fse {
class Commands;

class PlacementCommand : public QObject {
	Q_OBJECT

public:
	PlacementCommand(Commands* commands);
	virtual ~PlacementCommand();

	Q_INVOKABLE void setPosition(fsd::Placement* placement, const QVector3D& position);
	Q_INVOKABLE void setRotation(fsd::Placement* placement, const QVector3D& rotation);
	Q_INVOKABLE void setPlace(fsd::Placement* placement, fsd::Place* place);

protected:
	Commands* _c{ nullptr };
};
} // namespace fse

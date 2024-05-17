#pragma once

#include <QtCore/QObject>

#include <lh/data/Placement.hpp>

namespace lhe {
class Commands;

class PlacementCommand : public QObject {
	Q_OBJECT

public:
	PlacementCommand(Commands* commands);
	virtual ~PlacementCommand();

	Q_INVOKABLE void setPosition(lh::Placement* placement, const QVector3D& position);
	Q_INVOKABLE void setRotation(lh::Placement* placement, const QVector3D& rotation);
	Q_INVOKABLE void setPlace(lh::Placement* placement, lh::Place* place);

protected:
	Commands* _c{ nullptr };
};
} // namespace lhe

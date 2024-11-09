#pragma once

#include <QtCore/QObject>

#include <fsd/data/Placement.hpp>

namespace fse {
class Commands;

class PlacementCommand : public QObject {
	Q_OBJECT

public:
	explicit PlacementCommand(Commands* commands);
	~PlacementCommand() override;

	Q_INVOKABLE void setPlace(fsd::Placement* placement, fsd::Place* place);

private:
	Commands* _c{ nullptr };
};
} // namespace fse

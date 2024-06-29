#pragma once

#include <QtCore/QObject>

#include <fsd/data/Place.hpp>

namespace fse {
class Commands;

class PlaceCommand : public QObject {
	Q_OBJECT

public:
	PlaceCommand(Commands* commands);
	virtual ~PlaceCommand();

protected:
	Commands* _c{ nullptr };
};
} // namespace fse

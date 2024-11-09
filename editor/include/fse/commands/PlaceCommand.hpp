#pragma once

#include <QtCore/QObject>

#include <fsd/data/Place.hpp>

namespace fse {
class Commands;

class PlaceCommand : public QObject {
	Q_OBJECT

public:
	explicit PlaceCommand(Commands* commands);
	~PlaceCommand() override;

private:
	Commands* _c{ nullptr };
};
} // namespace fse

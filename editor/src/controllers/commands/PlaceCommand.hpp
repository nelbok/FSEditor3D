#pragma once

#include <QtCore/QObject>

#include <lh/data/Place.hpp>

namespace lhe {
class Commands;

class PlaceCommand : public QObject {
	Q_OBJECT

public:
	PlaceCommand(Commands* commands);
	virtual ~PlaceCommand();

protected:
	Commands* _c{ nullptr };
};
} // namespace lhe

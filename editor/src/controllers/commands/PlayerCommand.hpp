#pragma once

#include <QtCore/QObject>

#include <lh/data/Player.hpp>

namespace lhe {
class Commands;

class PlayerCommand : public QObject {
	Q_OBJECT

public:
	PlayerCommand(Commands* commands);
	virtual ~PlayerCommand();

protected:
	Commands* _c{ nullptr };
};
} // namespace lhe

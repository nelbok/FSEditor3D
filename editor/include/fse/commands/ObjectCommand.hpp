#pragma once

#include <QtCore/QObject>

#include <fsd/data/Object.hpp>

namespace fse {
class Commands;

class ObjectCommand : public QObject {
	Q_OBJECT

public:
	explicit ObjectCommand(Commands* commands);
	~ObjectCommand() override;

private:
	Commands* _c{ nullptr };
};
} // namespace fse

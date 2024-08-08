#pragma once

#include <QtCore/QObject>

#include <fsd/data/Object.hpp>

namespace fse {
class Commands;

class ObjectCommand : public QObject {
	Q_OBJECT

public:
	ObjectCommand(Commands* commands);
	virtual ~ObjectCommand();

protected:
	Commands* _c{ nullptr };
};
} // namespace fse

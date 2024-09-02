#pragma once

#include <QtCore/QObject>

#include <fsd/data/Entity.hpp>

namespace fse {
class Commands;

class EntityCommand : public QObject {
	Q_OBJECT

public:
	EntityCommand(Commands* commands);
	virtual ~EntityCommand();

	Q_INVOKABLE void setName(fsd::Entity* entity, const QString& name);

protected:
	Commands* _c{ nullptr };
};
} // namespace fse

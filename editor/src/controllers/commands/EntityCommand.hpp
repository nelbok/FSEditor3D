#pragma once

#include <QtCore/QObject>

#include <lh/data/Entity.hpp>

namespace lhe {
class Commands;

class EntityCommand : public QObject {
	Q_OBJECT

public:
	EntityCommand(Commands* commands);
	virtual ~EntityCommand();

	Q_INVOKABLE void setName(lh::Entity* entity, const QString& name);

protected:
	Commands* _c{ nullptr };
};
} // namespace lhe

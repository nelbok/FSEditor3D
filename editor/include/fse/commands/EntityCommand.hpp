#pragma once

#include <QtCore/QObject>

#include <fsd/data/Entity.hpp>

namespace fse {
class Commands;

class EntityCommand : public QObject {
	Q_OBJECT

public:
	explicit EntityCommand(Commands* commands);
	~EntityCommand() override;

	Q_INVOKABLE void setName(fsd::Entity* entity, const QString& name);

private:
	Commands* _c{ nullptr };
};
} // namespace fse

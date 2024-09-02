#include <fse/commands/EntityCommand.hpp>

#include <fse/commands/Commands.hpp>
#include <fse/commands/ValueCommand.hpp>

namespace fse {

EntityCommand::EntityCommand(Commands* commands)
	: QObject(commands)
	, _c{ commands } {
	assert(commands);
}

EntityCommand::~EntityCommand() {}

void EntityCommand::setName(fsd::Entity* e, const QString& newValue) {
	addValueCommand(_c, e, &fsd::Entity::setName, &fsd::Entity::name, newValue);
}

} // namespace fse

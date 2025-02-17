#include <fse/commands/EntityCommand.hpp>

#include <fse/commands/Commands.hpp>
#include <fse/commands/ValueCommand.hpp>

namespace fse {

EntityCommand::EntityCommand(Commands* commands)
	: QObject(commands)
	, _cmd{ commands } {
	assert(commands);
}

EntityCommand::~EntityCommand() = default;

void EntityCommand::setName(fsd::Entity* e, const QString& newValue) {
	addValueCommand(_cmd, e, &fsd::Entity::setName, &fsd::Entity::name, newValue);
}

} // namespace fse

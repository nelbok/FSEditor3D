#include "EntityCommand.hpp"

#include "../Commands.hpp"
#include "ValueCommand.hpp"

namespace lhe {

EntityCommand::EntityCommand(Commands* commands)
	: QObject(commands)
	, _c{ commands } {
	assert(commands);
}

EntityCommand ::~EntityCommand() {}

void EntityCommand::setName(lh::Entity* e, const QString& newValue) {
	addValueCommand(_c, e, &lh::Entity::setName, &lh::Entity::name, newValue);
}

} // namespace lhe

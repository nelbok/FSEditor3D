#include <fse/commands/LinkCommand.hpp>

#include <fse/commands/Commands.hpp>
#include <fse/commands/ValueCommand.hpp>

namespace fse {

LinkCommand::LinkCommand(Commands* commands)
	: QObject(commands)
	, _cmd{ commands } {
	assert(commands);
}

LinkCommand::~LinkCommand() = default;

void LinkCommand::setLink(fsd::Link* l, fsd::Link* newValue) {
	addValueCommand(_cmd, l, &fsd::Link::setLink, &fsd::Link::link, newValue);
}

} // namespace fse

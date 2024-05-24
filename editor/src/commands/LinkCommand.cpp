#include "LinkCommand.hpp"

#include "Commands.hpp"
#include "ValueCommand.hpp"

namespace lhe {

LinkCommand::LinkCommand(Commands* commands)
	: QObject(commands)
	, _c{ commands } {
	assert(commands);
}

LinkCommand::~LinkCommand() {}

void LinkCommand::setLink(lh::Link* l, lh::Link* newValue) {
	addValueCommand(_c, l, &lh::Link::setLink, &lh::Link::link, newValue);
}

} // namespace lhe

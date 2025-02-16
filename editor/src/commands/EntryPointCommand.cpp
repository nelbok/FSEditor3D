#include <fse/commands/EntryPointCommand.hpp>

#include <fse/commands/Commands.hpp>
#include <fse/commands/ValueCommand.hpp>

namespace fse {

EntryPointCommand::EntryPointCommand(Commands* commands)
	: QObject(commands)
	, _cmd{ commands } {
	assert(commands);
}

EntryPointCommand::~EntryPointCommand() = default;

void EntryPointCommand::setPosition(fsd::EntryPoint* ep, const QVector3D& newValue) {
	addValueCommand(_cmd, ep, &fsd::EntryPoint::setPosition, &fsd::EntryPoint::position, newValue);
}

void EntryPointCommand::setRotation(fsd::EntryPoint* ep, double newValue) {
	addValueCommand(_cmd, ep, &fsd::EntryPoint::setRotation, &fsd::EntryPoint::rotation, newValue);
}

void EntryPointCommand::setPlace(fsd::EntryPoint* ep, fsd::Place* newValue) {
	addValueCommand(_cmd, ep, &fsd::EntryPoint::setPlace, &fsd::EntryPoint::place, newValue);
}

} // namespace fse

#include <fse/commands/EntryPointCommand.hpp>

#include <fse/commands/Commands.hpp>
#include <fse/commands/ValueCommand.hpp>
#include <fse/managers/PreviewManager.hpp>

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

void EntryPointCommand::assignCameraCoordinates(fsd::EntryPoint* ep, fse::PreviewManager* mng) {
	QVector3D position = mng->cameraPosition();
	float rotation = mng->cameraRotation().y();

	// Round values...
	position.setX(std::roundf(position.x()));
	position.setY(std::roundf(position.y()));
	position.setZ(std::roundf(position.z()));
	rotation = std::roundf(rotation);

	_cmd->beginList();
	setPosition(ep, position);
	setRotation(ep, rotation);
	_cmd->endList();
}

} // namespace fse

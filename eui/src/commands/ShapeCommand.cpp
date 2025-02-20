#include <fse/commands/ShapeCommand.hpp>

#include <fse/commands/Commands.hpp>
#include <fse/commands/ValueCommand.hpp>

namespace fse {

ShapeCommand::ShapeCommand(Commands* commands)
	: QObject(commands)
	, _cmd{ commands } {
	assert(commands);
}

ShapeCommand::~ShapeCommand() = default;

void ShapeCommand::setModel(fsd::Shape* s, fsd::Model* newValue) {
	addValueCommand(_cmd, s, &fsd::Shape::setModel, &fsd::Shape::model, newValue);
}

} // namespace fse

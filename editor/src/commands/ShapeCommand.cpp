#include <fse/commands/ShapeCommand.hpp>

#include <fse/commands/Commands.hpp>
#include <fse/commands/ValueCommand.hpp>

namespace fse {

ShapeCommand::ShapeCommand(Commands* commands)
	: QObject(commands)
	, _c{ commands } {
	assert(commands);
}

ShapeCommand::~ShapeCommand() = default;

void ShapeCommand::setModel(fsd::Shape* s, fsd::Model* newValue) {
	addValueCommand(_c, s, &fsd::Shape::setModel, &fsd::Shape::model, newValue);
}

} // namespace fse

#include <fse/commands/ModelCommand.hpp>

#include <fse/commands/Commands.hpp>
#include <fse/commands/ValueCommand.hpp>

namespace fse {

ModelCommand::ModelCommand(Commands* commands)
	: QObject(commands)
	, _cmd{ commands } {
	assert(commands);
}

ModelCommand::~ModelCommand() = default;

void ModelCommand::setSourcePath(fsd::Model* m, const QUrl& newValue) {
	addValueCommand(_cmd, m, &fsd::Model::setSourcePath, &fsd::Model::sourcePath, newValue);
}

void ModelCommand::setQmlName(fsd::Model* m, const QString& newValue) {
	addValueCommand(_cmd, m, &fsd::Model::setQmlName, &fsd::Model::qmlName, newValue);
}

void ModelCommand::setModelType(fsd::Model* m, fsd::Model::ModelType newValue) {
	addValueCommand(_cmd, m, &fsd::Model::setModelType, &fsd::Model::modelType, newValue);
}

} // namespace fse

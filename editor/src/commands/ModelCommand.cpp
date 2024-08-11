#include "ModelCommand.hpp"

#include "Commands.hpp"
#include "ValueCommand.hpp"

namespace fse {

ModelCommand::ModelCommand(Commands* commands)
	: QObject(commands)
	, _c{ commands } {
	assert(commands);
}

ModelCommand::~ModelCommand() {}

void ModelCommand::setSourcePath(fsd::Model* m, const QUrl& newValue) {
	addValueCommand(_c, m, &fsd::Model::setSourcePath, &fsd::Model::sourcePath, newValue);
}

void ModelCommand::setQmlName(fsd::Model* m, const QString& newValue) {
	addValueCommand(_c, m, &fsd::Model::setQmlName, &fsd::Model::qmlName, newValue);
}

void ModelCommand::setModelType(fsd::Model* m, fsd::Model::ModelType newValue) {
	addValueCommand(_c, m, &fsd::Model::setModelType, &fsd::Model::modelType, newValue);
}

} // namespace fse

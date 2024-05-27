#include "ModelCommand.hpp"

#include "Commands.hpp"
#include "ValueCommand.hpp"

namespace lhe {

ModelCommand::ModelCommand(Commands* commands)
	: QObject(commands)
	, _c{ commands } {
	assert(commands);
}

ModelCommand::~ModelCommand() {}

void ModelCommand::setSourcePath(lh::Model* m, const QUrl& newValue) {
	addValueCommand(_c, m, &lh::Model::setSourcePath, &lh::Model::sourcePath, newValue);
}

void ModelCommand::setQmlName(lh::Model* m, const QString& newValue) {
	addValueCommand(_c, m, &lh::Model::setQmlName, &lh::Model::qmlName, newValue);
}

} // namespace lhe

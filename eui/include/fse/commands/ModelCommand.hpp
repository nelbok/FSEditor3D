#pragma once

#include <QtCore/QObject>

#include <fsd/data/Model.hpp>

namespace fse {
class Commands;

class ModelCommand : public QObject {
	Q_OBJECT

public:
	explicit ModelCommand(Commands* commands);
	~ModelCommand() override;

	Q_INVOKABLE void setSourcePath(fsd::Model* model, const QUrl& sourcePath);
	Q_INVOKABLE void setQmlName(fsd::Model* model, const QString& qmlName);
	Q_INVOKABLE void setModelType(fsd::Model* model, fsd::Model::ModelType type);

private:
	Commands* _cmd{ nullptr };
};
} // namespace fse

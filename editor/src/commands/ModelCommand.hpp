#pragma once

#include <QtCore/QObject>

#include <fsd/data/Model.hpp>

namespace fse {
class Commands;

class ModelCommand : public QObject {
	Q_OBJECT

public:
	ModelCommand(Commands* commands);
	virtual ~ModelCommand();

	Q_INVOKABLE void setSourcePath(fsd::Model* model, const QUrl& sourcePath);
	Q_INVOKABLE void setQmlName(fsd::Model* model, const QString& qmlName);
	Q_INVOKABLE void setType(fsd::Model* model, fsd::Model::Type type);

protected:
	Commands* _c{ nullptr };
};
} // namespace fse

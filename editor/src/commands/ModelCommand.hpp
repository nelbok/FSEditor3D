#pragma once

#include <QtCore/QObject>

#include <lh/data/Model.hpp>

namespace lhe {
class Commands;

class ModelCommand : public QObject {
	Q_OBJECT

public:
	ModelCommand(Commands* commands);
	virtual ~ModelCommand();

	Q_INVOKABLE void setSourcePath(lh::Model* model, const QUrl& sourcePath);
	Q_INVOKABLE void setQmlName(lh::Model* model, const QString& qmlName);
	Q_INVOKABLE void setType(lh::Model* model, lh::Model::Type type);

protected:
	Commands* _c{ nullptr };
};
} // namespace lhe

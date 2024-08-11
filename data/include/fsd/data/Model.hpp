#pragma once

#include <QtCore/QUrl>

#include <fsd/data/Entity.hpp>

namespace fsd {
class Project;

class Model : public Entity {
	Q_OBJECT
	Q_PROPERTY(QUrl sourcePath READ sourcePath WRITE setSourcePath NOTIFY sourcePathUpdated)
	Q_PROPERTY(QString qmlName READ qmlName WRITE setQmlName NOTIFY qmlNameUpdated)
	Q_PROPERTY(ModelType modelType READ modelType WRITE setModelType NOTIFY modelTypeUpdated)

public:
	enum class ModelType {
		Link,
		Place,
		Object,
	};
	Q_ENUM(ModelType)

	Model(Project* project);
	virtual ~Model();

	virtual void reset() override;
	void copy(const Model& model);

	const QUrl& sourcePath() const;
	void setSourcePath(const QUrl& path);

	const QString& qmlName() const;
	void setQmlName(const QString& path);

	ModelType modelType() const;
	void setModelType(ModelType type);

	virtual void load(const QJsonObject& json) override;
	virtual void save(QJsonObject& json) const override;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void sourcePathUpdated();
	void qmlNameUpdated();
	void modelTypeUpdated();
};
} // namespace fsd

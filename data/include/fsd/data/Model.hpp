#pragma once

#include <QtCore/QUrl>

#include <fsd/data/Entity.hpp>

namespace fsd {
class Project;

class Model : public Entity {
	Q_OBJECT
	Q_PROPERTY(QUrl sourcePath READ sourcePath WRITE setSourcePath NOTIFY sourcePathUpdated)
	Q_PROPERTY(QString qmlName READ qmlName WRITE setQmlName NOTIFY qmlNameUpdated)
	Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeUpdated)

public:
	enum class Type {
		Link,
		Place,
		Character,
	};
	Q_ENUM(Type)

	Model(Project* project);
	virtual ~Model();

	virtual void reset() override;
	void copy(const Model& model);

	const QUrl& sourcePath() const;
	void setSourcePath(const QUrl& path);

	const QString& qmlName() const;
	void setQmlName(const QString& path);

	Type type() const;
	void setType(Type type);

	virtual void load(const QJsonObject& json) override;
	virtual void save(QJsonObject& json) const override;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void sourcePathUpdated();
	void qmlNameUpdated();
	void typeUpdated();
};
} // namespace fsd

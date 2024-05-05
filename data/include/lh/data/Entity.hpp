#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUuid>

namespace lh {
class Project;

class Entity : public QObject {
	Q_OBJECT
	Q_PROPERTY(QUuid uuid READ uuid NOTIFY uuidUpdated)
	Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameUpdated)

public:
	Entity(Project* project);
	Entity(Project* project, QObject* parent);
	virtual ~Entity();

	virtual void reset();
	void copy(const Entity& entity);

	const QUuid& uuid() const;

	const QString& name() const;
	void setName(const QString& name);

	virtual void load(const QJsonObject& json);
	virtual void save(QJsonObject& json) const;

protected:
	void setUuid(const QUuid& uuid);

private:
	Project* _project{ nullptr };
	QUuid _uuid{};
	QString _name{};

signals:
	void uuidUpdated();
	void nameUpdated();
};
} // namespace lh

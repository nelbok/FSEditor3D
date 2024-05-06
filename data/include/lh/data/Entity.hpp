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
	Entity(QObject* parent = nullptr);
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
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void uuidUpdated();
	void nameUpdated();
};
} // namespace lh

/*
 * Copyright (c) 2024 Foxxy Soft.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution
 */

#pragma once

#include <fsd/data/FSDataExport.h>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUuid>

/**
 * @brief Main namespace for Foxxy Soft Data.
 */
namespace fsd {
class Project;

/**
 * @brief Main class of all entities with unique id and name.
 */
class FSDATA_EXPORT Entity : public QObject {
	Q_OBJECT
	/**
	 * @brief Unique id, the value is set automatically when calling reset() function, you shouldn't use the setter.
	 */
	Q_PROPERTY(QUuid uuid READ uuid WRITE setUuid NOTIFY uuidUpdated)
	/**
	 * @brief If an entity is alive, if it isn't, it will not be used by FileManager.
	 */
	Q_PROPERTY(bool isAlive READ isAlive WRITE setIsAlive NOTIFY isAliveUpdated)
	/**
	 * @brief The name of the entity.
	 */
	Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameUpdated)
	/**
	 * @brief If at least one entity has an UuidPointer of this entity.
	 */
	Q_PROPERTY(bool hasRef READ hasRef NOTIFY hasRefUpdated)
	/**
	 * @brief Type of the class that inherits Entity.
	 */
	Q_PROPERTY(Type type READ type CONSTANT)

public:
	/**
	 * @brief Type of the class that inherits Entity.
	 */
	enum class Type {
		Link,
		Model,
		Object,
		Place,
		Project,
	};
	Q_ENUM(Type)

	Project* project() const;

	virtual void reset();
	void copy(const Entity& entity);

	const QUuid& uuid() const;
	void setUuid(const QUuid& uuid);

	bool isAlive() const;
	void setIsAlive(bool isAlive);

	const QString& name() const;
	void setName(const QString& name);

	const QList<Entity*>& refs() const;
	void addRef(Entity* ref);
	void removeRef(Entity* ref);
	bool hasRef() const;

	virtual Type type() const = 0;

	virtual void load(const QJsonObject& json);
	virtual void save(QJsonObject& json) const;

protected:
	Entity(Project* project, QObject* parent = nullptr);
	~Entity() override;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void uuidUpdated();
	void isAliveUpdated();
	void nameUpdated();
	void hasRefUpdated();
};
} // namespace fsd

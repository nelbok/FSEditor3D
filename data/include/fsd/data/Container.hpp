/*
 * Copyright (c) 2024 Foxxy Soft.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution
 */

#pragma once

#include <fsd/data/FSDataExport.h>

#include <QtCore/QObject>

namespace fsd {

class Entity;
class Project;

/**
 * @brief Base class for Container.
 */
class FSDATA_EXPORT BaseContainer : public QObject {
	Q_OBJECT
protected:
	explicit BaseContainer(Project* project);
	~BaseContainer() override;

protected:
	Project* _project{ nullptr };

signals:
	void updated();
};

/**
 * @brief Container of entities
 * @param TType An Entity subclass
 *
 * Wrapper around the list.\n
 * Send a signal when the list is updated.
 */
template<class TType>
class FSDATA_EXPORT Container : public BaseContainer {
public:
	explicit Container(Project* project)
		: BaseContainer(project) {
		static_assert(std::is_base_of<Entity, TType>::value, "TType must inherit from Entity");
	}
	~Container() override = default;

	QList<TType*> get() const {
		return _entities;
	}

	void set(const QList<TType*>& entities) {
		if (_entities != entities) {
			_entities = entities;
			emit updated();
		}
	}

	TType* at(qsizetype i) const {
		assert(i < _entities.size());
		return _entities.at(i);
	}

	qsizetype size() const {
		return _entities.size();
	}

	TType* create() {
		auto* entity = new TType(_project);
		entity->reset();
		_entities.append(entity);
		emit updated();
		return entity;
	}

	void remove(TType* value) {
		assert(value);
		assert(_entities.contains(value));
		_entities.removeAll(value);
		value->deleteLater();
		emit updated();
	}

	TType* duplicate(TType* value) {
		auto* entity = new TType(_project);
		entity->copy(*value);
		entity->setName(entity->name() + "*");
		_entities.append(entity);
		emit updated();
		return entity;
	}

	void clean() {
		for (auto* entity : _entities) {
			entity->reset();
			entity->deleteLater();
		}
		_entities.clear();
		emit updated();
	}

private:
	QList<TType*> _entities;
};
} // namespace fsd

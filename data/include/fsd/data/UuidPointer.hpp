/*
 * Copyright (c) 2024 Foxxy Soft.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution
 */

#pragma once

#include <QtCore/QObject>
#include <QtCore/QUuid>

namespace fsd {

class Entity;
class Project;

/**
 * @brief Base class for UuidPointer.
 */
class BasePointer : public QObject {
	Q_OBJECT
public:
	const QUuid& uuid() const;
	bool setUuid(const QUuid& uuid);

	/**
   * @brief Return true if uuid is null.
   */
	bool isNull() const;

protected slots:
	virtual void update() = 0;

protected:
	BasePointer(Project* project, void (Project::*signal)(), Entity* parent);
	~BasePointer() override;

	Project* _project{ nullptr };
	Entity* _ref{ nullptr };
	QUuid _uuid{};
};

/**
 * @brief Pointer to value with Uuid as ID
 * @param T An Entity subclass
 *
 * Connect two entities by their Uuid instead of their instance.\n
 * Use get() to get the instance.\n
 * Use uuid() to get the uuid.
 *
 * Even if the instance is not known at the loading, the pointer will not be destroyed and the uuid will not be updated.\n
 * Though, if no instance corresponding to the uuid is found, the pointer will not be valid.
 */
template<class T>
class UuidPointer : public BasePointer {
public:
	UuidPointer(Project* project, const QList<T*>& (Project::*getter)() const, void (Project::*signal)(), Entity* parent)
		: BasePointer(project, signal, parent)
		, _getter{ getter } {
		assert(_getter);
		static_assert(std::is_base_of<Entity, T>::value, "T must inherit from Entity");
	}
	~UuidPointer() override = default;

	T* operator->() {
		return get();
	}

	/**
   * @brief Return true if the instance is valid. Call this function before trying to get the instance.
   */
	bool valid() const {
		assert(_project);
		return _entity != nullptr;
	}

	T* get() const {
		assert(_project);
		assert(_entity);
		return _entity;
	}

	bool set(T* entity) {
		assert(_project);
		bool changed = _entity != entity;
		if (changed) {
			_uuid = entity ? entity->uuid() : QUuid{};
			if (_entity) {
				_entity->removeRef(_ref);
			}
			_entity = entity;
			if (_entity) {
				_entity->addRef(_ref);
			}
		}
		return changed;
	}

protected:
	void update() override {
		assert(_project);
		assert(_getter);
		if (_entity) {
			_entity->removeRef(_ref);
		}
		_entity = nullptr;
		const auto& datas = (_project->*_getter)();
		for (auto* data : datas) {
			if (data->uuid() == _uuid) {
				_entity = data;
				_entity->addRef(_ref);
			}
		}
	}

private:
	T* _entity{ nullptr };
	const QList<T*>& (Project::*_getter)() const { nullptr };
};

UuidPointer<class Link>* makeLinkPointer(Project* project, Entity* parent);
UuidPointer<class Model>* makeModelPointer(Project* project, Entity* parent);
UuidPointer<class Object>* makeObjectPointer(Project* project, Entity* parent);
UuidPointer<class Place>* makePlacePointer(Project* project, Entity* parent);
} // namespace fsd

/*
 * Copyright (c) 2024 Foxxy Soft.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution
 */

#pragma once

#include <fsd/data/FSDataExport.h>

#include <QtCore/QObject>
#include <QtCore/QUuid>

#include <fsd/data/Container.hpp>

namespace fsd {

class Entity;
class Project;

/**
 * @brief Base class for UuidPointer.
 */
class FSDATA_EXPORT BasePointer : public QObject {
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
	BasePointer(BaseContainer* datas, Entity* parent);
	~BasePointer() override;

	Entity* _ref{ nullptr };
	QUuid _uuid{};
};

/**
 * @brief Pointer to value with Uuid as ID
 * @param TType An Entity subclass
 *
 * Connect two entities by their Uuid instead of their instance.\n
 * Use get() to get the instance.\n
 * Use uuid() to get the uuid.
 *
 * Even if the instance is not known at the loading, the pointer will not be destroyed and the uuid will not be updated.\n
 * Though, if no instance corresponding to the uuid is found, the pointer will not be valid.
 */
template<class TType>
class FSDATA_EXPORT UuidPointer : public BasePointer {
public:
	UuidPointer(Container<TType>* datas, Entity* parent)
		: BasePointer(datas, parent)
		, _datas{ datas } {
		assert(_datas);
		static_assert(std::is_base_of<Entity, TType>::value, "TType must inherit from Entity");
	}
	~UuidPointer() override = default;

	TType* operator->() {
		return get();
	}

	/**
   * @brief Return true if the instance is valid. Call this function before trying to get the instance.
   */
	bool valid() const {
		assert(_datas);
		return _entity != nullptr;
	}

	TType* get() const {
		assert(_datas);
		assert(_entity);
		return _entity;
	}

	bool set(TType* entity) {
		assert(_datas);
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
		assert(_datas);
		if (_entity) {
			_entity->removeRef(_ref);
		}
		_entity = nullptr;
		for (auto* data : _datas->get()) {
			if (data->uuid() == _uuid) {
				_entity = data;
				_entity->addRef(_ref);
			}
		}
	}

private:
	TType* _entity{ nullptr };
	Container<TType>* _datas{ nullptr };
};

UuidPointer<class Link>* makeLinkPointer(Project* project, Entity* parent);
UuidPointer<class Model>* makeModelPointer(Project* project, Entity* parent);
UuidPointer<class Object>* makeObjectPointer(Project* project, Entity* parent);
UuidPointer<class Place>* makePlacePointer(Project* project, Entity* parent);
} // namespace fsd

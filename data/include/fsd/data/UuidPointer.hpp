#pragma once

#include <QtCore/QObject>
#include <QtCore/QUuid>

namespace fsd {

class Entity;
class Project;

class BasePointer : public QObject {
	Q_OBJECT
public:
	const QUuid& uuid() const;
	bool setUuid(const QUuid& uuid);
	bool isNull() const;

protected slots:
	virtual void update() = 0;

protected:
	BasePointer(Project* project, void (Project::*signal)(), Entity* parent);
	virtual ~BasePointer();

	Project* _project{ nullptr };
	Entity* _ref{ nullptr };
	QUuid _uuid{};
};

template<class T>
class UuidPointer : public BasePointer {
public:
	UuidPointer(Project* project, const QList<T*>& (Project::*getter)() const, void (Project::*signal)(), Entity* parent)
		: BasePointer(project, signal, parent)
		, _getter{ getter } {
		assert(_getter);
	}
	virtual ~UuidPointer() {}

	T* operator->() {
		return get();
	}

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
			_uuid = (entity) ? entity->uuid() : QUuid{};
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
	virtual void update() override {
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

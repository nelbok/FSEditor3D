#pragma once

#include <QtCore/QObject>
#include <QtCore/QUuid>

namespace lh {

class Project;

class BasePointer : public QObject {
	Q_OBJECT
public:
	BasePointer(Project* project, void (Project::*signal)(), QObject* parent = nullptr);
	virtual ~BasePointer();

	const QUuid& uuid() const;
	bool setUuid(const QUuid& uuid);
	bool isNull() const;

protected slots:
	virtual void update() = 0;

protected:
	Project* _project{ nullptr };
	QUuid _uuid{};
};

template<class T>
class UuidPointer : public BasePointer {
public:
	UuidPointer(Project* project, const QList<T*>& (Project::*getter)() const, void (Project::*signal)(), QObject* parent = nullptr)
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
			_entity = entity;
		}
		return changed;
	}

protected:
	virtual void update() override {
		assert(_project);
		assert(_getter);
		_entity = nullptr;
		const auto& datas = (_project->*_getter)();
		for (auto* data : datas) {
			if (data->uuid() == _uuid) {
				_entity = data;
			}
		}
	}

private:
	T* _entity{ nullptr };
	const QList<T*>& (Project::*_getter)() const { nullptr };
};

UuidPointer<class Character>* makeCharacterPointer(Project* project, QObject* parent);
UuidPointer<class Link>* makeLinkPointer(Project* project, QObject* parent);
UuidPointer<class Place>* makePlacePointer(Project* project, QObject* parent);
} // namespace lh

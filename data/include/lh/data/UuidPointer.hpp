#pragma once

#include <mutex>

#include <QtCore/QObject>
#include <QtCore/QUuid>

namespace lh {

class Project;

template<class T>
class UuidPointer {
public:
	UuidPointer() {}
	virtual ~UuidPointer() {}

	T* operator->() {
		return get();
	}

	void init(Project* project, const QList<T*>& (Project::*getter)() const, void (Project::*signal)(), QObject* parent) {
		assert(!_project);
		assert(project);
		assert(getter);
		assert(signal);
		assert(parent);

		_project = project;
		_getter = getter;

		QObject::connect(project, signal, parent, [this]() {
			update();
		});
		update();
	}

	bool valid() const {
		assert(_project);
		const std::lock_guard<std::mutex> lock(_mutex);
		return _entity != nullptr;
	}

	bool isNull() const {
		assert(_project);
		const std::lock_guard<std::mutex> lock(_mutex);
		return _uuid.isNull();
	}

	T* get() const {
		assert(_project);
		const std::lock_guard<std::mutex> lock(_mutex);
		assert(_entity);
		return _entity;
	}

	const QUuid& uuid() const {
		assert(_project);
		return _uuid;
	}

	bool setUuid(const QUuid& uuid) {
		assert(_project);
		bool changed = _uuid != uuid;
		if (changed) {
			{
				const std::lock_guard<std::mutex> lock(_mutex);
				_uuid = uuid;
			}
			update();
		}
		return changed;
	}

	bool set(T* entity) {
		assert(_project);
		bool changed = _entity != entity;
		if (changed) {
			const std::lock_guard<std::mutex> lock(_mutex);
			_uuid = (entity) ? entity->uuid() : QUuid{};
			_entity = entity;
		}
		return changed;
	}

private:
	void update() {
		assert(_project);
		assert(_getter);
		const std::lock_guard<std::mutex> lock(_mutex);
		_entity = nullptr;
		const auto& datas = (_project->*_getter)();
		for (auto* data : datas) {
			if (data->uuid() == _uuid) {
				_entity = data;
			}
		}
	}

	QUuid _uuid{};
	T* _entity{ nullptr };
	Project* _project{ nullptr };
	const QList<T*>& (Project::*_getter)() const { nullptr };
	mutable std::mutex _mutex{};
};

void initCharacterPointer(UuidPointer<class Character>& ptr, Project* project, QObject* parent);
void initLinkPointer(UuidPointer<class Link>& ptr, Project* project, QObject* parent);
void initPlacePointer(UuidPointer<class Place>& ptr, Project* project, QObject* parent);
} // namespace lh

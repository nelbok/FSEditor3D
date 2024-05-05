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

	UuidPointer(Project* project, const QList<T*>& (Project::*getter)() const, void (Project::*signal)())
		: _project(project)
		, _getter(getter)
		, _signal(signal) {
		assert(project);
		assert(getter);
		assert(signal);

		_connection = QObject::connect(project, signal, project, [this]() {
			update();
		});
		update();
	}
	virtual ~UuidPointer() {
		QObject::disconnect(_connection);
	}

	void operator=(const UuidPointer<T>& right) {
		assert(right._project);
		assert(right._getter);
		assert(right._signal);

		this->_uuid = right._uuid;
		this->_project = right._project;
		this->_getter = right._getter;
		this->_signal = right._signal;

		QObject::disconnect(_connection);
		_connection = QObject::connect(_project, _signal, _project, [this]() {
			update();
		});
		update();
	}

	T* operator->() {
		return get();
	}

	bool valid() const {
		const std::lock_guard<std::mutex> lock(_mutex);
		return _entity != nullptr;
	}

	bool isNull() const {
		const std::lock_guard<std::mutex> lock(_mutex);
		return _uuid.isNull();
	}

	T* get() const {
		const std::lock_guard<std::mutex> lock(_mutex);
		assert(_entity);
		return _entity;
	}

	const QUuid& uuid() const {
		return _uuid;
	}

	void setUuid(const QUuid& uuid) {
		// FIXME
		bool changed = false;
		if (_uuid != uuid) {
			const std::lock_guard<std::mutex> lock(_mutex);
			changed = true;
			_uuid = uuid;
		}
		if (changed) {
			update();
		}
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
	void (Project::*_signal)(){ nullptr };
	mutable std::mutex _mutex{};
	QMetaObject::Connection _connection{};
};

UuidPointer<class Place> makePlacePointer(Project* project);
} // namespace lh

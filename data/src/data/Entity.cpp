#include <lh/data/Entity.hpp>
#include <lh/data/Project.hpp>
#include <lh/io/Json.hpp>

namespace lh {
Entity::Entity(Project* project)
	: QObject(project)
	, _project{ project } {
	Entity::reset();
}

Entity::Entity(Project* project, QObject* parent)
	: QObject(parent)
	, _project{ project } {
	Entity::reset();
}

Entity::~Entity() {}

const QUuid& Entity::uuid() const {
	return _uuid;
}

const QString& Entity::name() const {
	return _name;
}

void Entity::setUuid(const QUuid& uuid) {
	if (_uuid != uuid) {
		_uuid = uuid;
		emit uuidUpdated();
	}
}

void Entity::setName(const QString& name) {
	if (_name != name) {
		_name = name;
		emit nameUpdated();
	}
}

void Entity::reset() {
	setUuid(QUuid::createUuid());
	setName("Default");
}

void Entity::copy(const Entity& entity) {
	setName(entity.name());
}

constexpr auto luuid = "uuid";
constexpr auto lname = "name";

void Entity::load(const QJsonObject& json) {
	setUuid(Json::toUuid(Json::toValue(luuid, json)));
	setName(Json::toString(lname, json));
}

void Entity::save(QJsonObject& json) const {
	json[luuid] = Json::fromUuid(_uuid);
	json[lname] = _name;
}
} // namespace lh

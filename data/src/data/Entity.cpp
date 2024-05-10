#include <lh/data/Entity.hpp>

#include <lh/io/Json.hpp>

#include "common/Tools.hpp"

namespace lh {
struct Entity::Impl {
	QUuid uuid{};
	QString name{};
};

Entity::Entity(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

Entity::~Entity() {}

void Entity::reset() {
	setUuid(QUuid::createUuid());
	setName("Default");
}

void Entity::copy(const Entity& entity) {
	setUuid(QUuid::createUuid());
	setName(entity.name());
}

const QUuid& Entity::uuid() const {
	return _impl->uuid;
}

const QString& Entity::name() const {
	return _impl->name;
}

void Entity::setUuid(const QUuid& uuid) {
	TOOLS_SETTER(Entity, uuid);
}

void Entity::setName(const QString& name) {
	TOOLS_SETTER(Entity, name);
}

constexpr auto lUuid = "uuid";
constexpr auto lName = "name";

void Entity::load(const QJsonObject& json) {
	setUuid(Json::toUuid(Json::toValue(lUuid, json)));
	setName(Json::toString(lName, json));
}

void Entity::save(QJsonObject& json) const {
	json[lUuid] = Json::fromUuid(_impl->uuid);
	json[lName] = _impl->name;
}
} // namespace lh

#include <lh/data/Entity.hpp>

#include <lh/io/Json.hpp>

#include "common/Accessors.hpp"

namespace lh {
struct Entity::Impl {
	QUuid uuid{};
	bool isAlive{ true };
	QString name{};
	QList<Entity*> refs{};
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

void Entity::setUuid(const QUuid& uuid) {
	TOOLS_SETTER(Entity, uuid);
}

bool Entity::isAlive() const {
	return _impl->isAlive;
}

void Entity::setIsAlive(bool isAlive) {
	TOOLS_SETTER(Entity, isAlive);
}

const QString& Entity::name() const {
	return _impl->name;
}

void Entity::setName(const QString& name) {
	TOOLS_SETTER(Entity, name);
}

const QList<Entity*>& Entity::refs() const {
	return _impl->refs;
}

void Entity::addRef(Entity* ref) {
	assert(ref);
	assert(!_impl->refs.contains(ref));
	_impl->refs.append(ref);
	emit hasRefUpdated();
}

void Entity::removeRef(Entity* ref) {
	assert(ref);
	assert(_impl->refs.contains(ref));
	_impl->refs.removeAll(ref);
	emit hasRefUpdated();
}

bool Entity::hasRef() {
	return !_impl->refs.empty();
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

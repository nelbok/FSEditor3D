#include <lh/data/Entity.hpp>

#include <lh/io/Json.hpp>

namespace lh {
struct Entity::Impl {
	QUuid uuid{};
	QString name{};
};

Entity::Entity(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

Entity::~Entity() {}

const QUuid& Entity::uuid() const {
	return _impl->uuid;
}

const QString& Entity::name() const {
	return _impl->name;
}

void Entity::setUuid(const QUuid& uuid) {
	if (_impl->uuid != uuid) {
		_impl->uuid = uuid;
		emit uuidUpdated();
	}
}

void Entity::setName(const QString& name) {
	if (_impl->name != name) {
		_impl->name = name;
		emit nameUpdated();
	}
}

void Entity::reset() {
	setUuid(QUuid::createUuid());
	setName("Default");
}

void Entity::copy(const Entity& entity) {
	setUuid(QUuid::createUuid());
	setName(entity.name());
}

constexpr auto luuid = "uuid";
constexpr auto lname = "name";

void Entity::load(const QJsonObject& json) {
	setUuid(Json::toUuid(Json::toValue(luuid, json)));
	setName(Json::toString(lname, json));
}

void Entity::save(QJsonObject& json) const {
	json[luuid] = Json::fromUuid(_impl->uuid);
	json[lname] = _impl->name;
}
} // namespace lh

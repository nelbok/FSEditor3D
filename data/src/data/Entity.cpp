#include <fsd/data/Entity.hpp>

namespace fsd {
struct Entity::Impl {
	Project* project{ nullptr };
	QUuid uuid{};
	bool isAlive{ true };
	QString name{};
	QList<Entity*> refs{};
};

Entity::Entity(Project* project, QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {
	assert(project);
	setObjectName("Entity");
	_impl->project = project;
}

Entity::~Entity() = default;

Project* Entity::project() const {
	return _impl->project;
}

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

QString Entity::name() const {
	return _impl->name;
}

void Entity::setName(const QString& name) {
	TOOLS_SETTER(Entity, name);
}

QList<Entity*> Entity::refs() const {
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

bool Entity::hasRef() const {
	return !_impl->refs.empty();
}

void Entity::load(const QJsonObject& json) {
	setUuid(Json::toUuid(objectName(), Format::lUuid, json));
	setName(Json::toString(objectName(), Format::lName, json));
}

void Entity::save(QJsonObject& json) const {
	json[Format::lUuid] = Json::fromUuid(_impl->uuid);
	json[Format::lName] = _impl->name;
}
} // namespace fsd

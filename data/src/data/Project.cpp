#include <fsd/data/Project.hpp>

#include <QtCore/QCoreApplication>
#include <QtCore/QThread>

#include <fsd/data/Link.hpp>
#include <fsd/data/Model.hpp>
#include <fsd/data/Object.hpp>
#include <fsd/data/Place.hpp>
#include <fsd/data/UuidPointer.hpp>
#include <fsd/io/Format.hpp>
#include <fsd/io/Json.hpp>
#include <fsd/io/JsonException.hpp>

#include "common/Accessors.hpp"

namespace fsd {

struct Project::Impl {
	UuidPointer<Place>* defaultPlace{ nullptr };
	QUrl path{};
	bool isTemp{ true };
	QList<Entity*> entities{};
	QList<Link*> links{};
	QList<Model*> models{};
	QList<Object*> objects{};
	QList<Place*> places{};

	bool isInterruptionRequested(const Project* project) const {
		if (const auto* thread = project->thread(); thread != QCoreApplication::instance()->thread()) {
			return thread->isInterruptionRequested();
		}
		return false;
	}

	template<class TClass>
	void loadList(Project* project, QList<TClass*>& list, const QString& key, const QJsonObject& json, void (Project::*signal)()) const {
		list.clear();
		const auto& jsonArray = Json::toArray(key, json);
		for (const auto& jsonEntity : jsonArray) {
			if (!jsonEntity.isObject()) {
				throw JsonException(JsonException::Error::InvalidObject);
			}
			auto* entity = new TClass(project);
			entity->load(jsonEntity.toObject());
			list.append(entity);
			if (isInterruptionRequested(project)) {
				return;
			}
		}
		emit(project->*signal)();
	}

	template<class TClass>
	void saveList(const Project* project, const QList<TClass*>& list, const QString& key, QJsonObject& json) const {
		QJsonArray jsonArray;
		for (auto* entity : list) {
			if (!entity->isAlive())
				continue;

			QJsonObject jsonEntity;
			entity->save(jsonEntity);
			jsonArray.append(jsonEntity);
			if (isInterruptionRequested(project)) {
				return;
			}
		}
		json[key] = jsonArray;
	}
};

Project::Project(QObject* parent)
	: Geometry(this, parent)
	, _impl{ std::make_unique<Impl>() } {
	_impl->defaultPlace = makePlacePointer(this, this);
}

Project::~Project() = default;

void Project::reset() {
	Geometry::reset();

	// Reset datas
	setDefaultPlace(nullptr);
	cleanLinks();
	cleanModels();
	cleanObjects();
	cleanPlaces();
}

Place* Project::defaultPlace() const {
	return (_impl->defaultPlace->valid()) ? _impl->defaultPlace->get() : nullptr;
}

void Project::setDefaultPlace(Place* defaultPlace) {
	if (_impl->defaultPlace->set(defaultPlace)) {
		emit defaultPlaceUpdated();
	}
}

const QList<Entity*>& Project::entities() const {
	return _impl->entities;
}

const QList<Link*>& Project::links() const {
	return _impl->links;
}

void Project::setLinks(const QList<Link*>& links) {
	TOOLS_SETTER(Project, links);
	rebuildEntities();
}

Link* Project::createLink() {
	TOOLS_CREATE_ENTITY(Project, links);
	addEntity(entity);
	return entity;
}

void Project::removeLink(Link* link) {
	TOOLS_REMOVE_ENTITY(Project, link);
	removeEntity(link);
}

Link* Project::duplicateLink(Link* link) {
	TOOLS_DUPLICATE_ENTITY(Project, link);
	addEntity(entity);
	return entity;
}

void Project::cleanLinks() {
	TOOLS_CLEAN_ENTITIES(Project, links);
	rebuildEntities();
}

const QList<Model*>& Project::models() const {
	return _impl->models;
}

void Project::setModels(const QList<Model*>& models) {
	TOOLS_SETTER(Project, models);
	rebuildEntities();
}

Model* Project::createModel() {
	TOOLS_CREATE_ENTITY(Project, models);
	addEntity(entity);
	return entity;
}

void Project::removeModel(Model* model) {
	TOOLS_REMOVE_ENTITY(Project, model);
	removeEntity(model);
}

Model* Project::duplicateModel(Model* model) {
	TOOLS_DUPLICATE_ENTITY(Project, model);
	addEntity(entity);
	return entity;
}

void Project::cleanModels() {
	TOOLS_CLEAN_ENTITIES(Project, models);
	rebuildEntities();
}

const QList<Object*>& Project::objects() const {
	return _impl->objects;
}

void Project::setObjects(const QList<Object*>& objects) {
	TOOLS_SETTER(Project, objects);
	rebuildEntities();
}

Object* Project::createObject() {
	TOOLS_CREATE_ENTITY(Project, objects);
	addEntity(entity);
	return entity;
}

void Project::removeObject(Object* object) {
	TOOLS_REMOVE_ENTITY(Project, object);
	removeEntity(object);
}

Object* Project::duplicateObject(Object* object) {
	TOOLS_DUPLICATE_ENTITY(Project, object);
	addEntity(entity);
	return entity;
}

void Project::cleanObjects() {
	TOOLS_CLEAN_ENTITIES(Project, objects);
	rebuildEntities();
}

const QList<Place*>& Project::places() const {
	return _impl->places;
}

void Project::setPlaces(const QList<Place*>& places) {
	TOOLS_SETTER(Project, places);
	rebuildEntities();
}

Place* Project::createPlace() {
	TOOLS_CREATE_ENTITY(Project, places);
	addEntity(entity);
	return entity;
}

void Project::removePlace(Place* place) {
	TOOLS_REMOVE_ENTITY(Project, place);
	removeEntity(place);
}

Place* Project::duplicatePlace(Place* place) {
	TOOLS_DUPLICATE_ENTITY(Project, place);
	addEntity(entity);
	return entity;
}

void Project::cleanPlaces() {
	TOOLS_CLEAN_ENTITIES(Project, places);
	rebuildEntities();
}

Project::Type Project::type() const {
	return Type::Project;
}

void Project::load(const QJsonObject& json) {
	reset();
	Geometry::load(json);

	// Ordered to prevent crash related by UuidPointer
	_impl->loadList(this, _impl->models, Format::lModels, json, &Project::modelsUpdated);
	_impl->loadList(this, _impl->places, Format::lPlaces, json, &Project::placesUpdated);
	_impl->loadList(this, _impl->links, Format::lLinks, json, &Project::linksUpdated);
	_impl->loadList(this, _impl->objects, Format::lObjects, json, &Project::objectsUpdated);

	rebuildEntities();

	_impl->defaultPlace->setUuid(Json::toUuid(Json::toValue(Format::lDefaultPlaces, json)));
	emit defaultPlaceUpdated();
}

void Project::save(QJsonObject& json) const {
	Geometry::save(json);
	_impl->saveList(this, _impl->models, Format::lModels, json);
	_impl->saveList(this, _impl->places, Format::lPlaces, json);
	_impl->saveList(this, _impl->links, Format::lLinks, json);
	_impl->saveList(this, _impl->objects, Format::lObjects, json);
	json[Format::lDefaultPlaces] = Json::fromUuid(_impl->defaultPlace->uuid());
}

void Project::addEntity(Entity* entity) {
	assert(entity);
	assert(!_impl->entities.contains(entity));
	_impl->entities.push_back(entity);
	emit entitiesUpdated();
}

void Project::removeEntity(Entity* entity) {
	assert(entity);
	assert(_impl->entities.contains(entity));
	_impl->entities.removeAll(entity);
	emit entitiesUpdated();
}

void Project::rebuildEntities() {
	_impl->entities.clear();
	for (auto* link : _impl->links) {
		_impl->entities.push_back(link);
	}
	for (auto* model : _impl->models) {
		_impl->entities.push_back(model);
	}
	for (auto* object : _impl->objects) {
		_impl->entities.push_back(object);
	}
	for (auto* place : _impl->places) {
		_impl->entities.push_back(place);
	}
	emit entitiesUpdated();
}

} // namespace fsd

#include <fsd/data/Project.hpp>

#include <QtCore/QCoreApplication>
#include <QtCore/QThread>

#include <fsd/data/EntryPoint.hpp>
#include <fsd/data/Container.hpp>
#include <fsd/data/Link.hpp>
#include <fsd/data/Model.hpp>
#include <fsd/data/Object.hpp>
#include <fsd/data/Place.hpp>
#include <fsd/data/UuidPointer.hpp>
#include <fsd/io/Format.hpp>
#include <fsd/io/Json.hpp>
#include <fsd/io/JsonException.hpp>

namespace fsd {

struct Project::Impl {
	UuidPointer<Place>* defaultPlace{ nullptr };
	QList<Entity*> entities{};
	Container<EntryPoint>* entryPoints{ nullptr };
	Container<Link>* links{ nullptr };
	Container<Model>* models{ nullptr };
	Container<Object>* objects{ nullptr };
	Container<Place>* places{ nullptr };

	bool isInterruptionRequested(const Project* project) const {
		if (const auto* thread = project->thread(); thread != QCoreApplication::instance()->thread()) {
			return thread->isInterruptionRequested();
		}
		return false;
	}

	template<class TClass>
	Container<TClass>* initList(Project* project, void (Project::*signal)()) const {
		auto* data = new Container<TClass>(project);
		connect(data, &Container<TClass>::updated, project, &Project::rebuildEntities);
		connect(data, &Container<TClass>::updated, project, signal);
		return data;
	}

	template<class TClass>
	void loadList(Project* project, Container<TClass>* data, const QString& key, const QJsonObject& json) const {
		data->clean();
		QList<TClass*> list;
		const auto& jsonArray = Json::toArray(project->objectName(), key, json);
		for (const auto& jsonEntity : jsonArray) {
			if (!jsonEntity.isObject()) {
				throw JsonException(project->objectName(), key, JsonException::Error::InvalidObject);
			}
			auto* entity = new TClass(project);
			entity->load(jsonEntity.toObject());
			list.append(entity);
			if (isInterruptionRequested(project)) {
				return;
			}
		}
		data->set(list);
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
	// Init list before everything
	_impl->entryPoints = _impl->initList<fsd::EntryPoint>(this, &Project::entryPointsUpdated);
	_impl->links = _impl->initList<fsd::Link>(this, &Project::linksUpdated);
	_impl->models = _impl->initList<fsd::Model>(this, &Project::modelsUpdated);
	_impl->objects = _impl->initList<fsd::Object>(this, &Project::objectsUpdated);
	_impl->places = _impl->initList<fsd::Place>(this, &Project::placesUpdated);

	// Other initialization
	_impl->defaultPlace = makePlacePointer(this, this);
	setObjectName("Project");
}

Project::~Project() = default;

void Project::reset() {
	Geometry::reset();

	// Reset datas
	setDefaultPlace(nullptr);
	_impl->entryPoints->clean();
	_impl->links->clean();
	_impl->models->clean();
	_impl->objects->clean();
	_impl->places->clean();
}

Place* Project::defaultPlace() const {
	return (_impl->defaultPlace->valid()) ? _impl->defaultPlace->get() : nullptr;
}

void Project::setDefaultPlace(Place* defaultPlace) {
	if (_impl->defaultPlace->set(defaultPlace)) {
		emit defaultPlaceUpdated();
	}
}

QList<Entity*> Project::entities() const {
	return _impl->entities;
}

Container<EntryPoint>* Project::entryPoints() const {
	return _impl->entryPoints;
}

Container<Link>* Project::links() const {
	return _impl->links;
}

Container<Model>* Project::models() const {
	return _impl->models;
}

Container<Object>* Project::objects() const {
	return _impl->objects;
}

Container<Place>* Project::places() const {
	return _impl->places;
}

Project::Type Project::type() const {
	return Type::Project;
}

void Project::load(const QJsonObject& json) {
	QSignalBlocker blocker(this);
	reset();
	blocker.unblock();
	Geometry::load(json);

	// Ordered to prevent crash related by UuidPointer
	blocker.reblock();
	_impl->loadList(this, _impl->models, Format::lModels, json);
	_impl->loadList(this, _impl->places, Format::lPlaces, json);
	_impl->loadList(this, _impl->links, Format::lLinks, json);
	_impl->loadList(this, _impl->objects, Format::lObjects, json);
	_impl->loadList(this, _impl->entryPoints, Format::lEntryPoints, json);
	blocker.unblock();

	emit modelsUpdated();
	emit placesUpdated();
	emit linksUpdated();
	emit objectsUpdated();
	emit entryPointsUpdated();
	rebuildEntities();

	_impl->defaultPlace->setUuid(Json::toUuid(objectName(), Format::lDefaultPlaces, json));
	emit defaultPlaceUpdated();
}

void Project::save(QJsonObject& json) const {
	Geometry::save(json);
	_impl->saveList(this, _impl->models->get(), Format::lModels, json);
	_impl->saveList(this, _impl->places->get(), Format::lPlaces, json);
	_impl->saveList(this, _impl->links->get(), Format::lLinks, json);
	_impl->saveList(this, _impl->objects->get(), Format::lObjects, json);
	_impl->saveList(this, _impl->entryPoints->get(), Format::lEntryPoints, json);
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
	for (auto* entryPoint : _impl->entryPoints->get()) {
		_impl->entities.push_back(entryPoint);
	}
	for (auto* link : _impl->links->get()) {
		_impl->entities.push_back(link);
	}
	for (auto* model : _impl->models->get()) {
		_impl->entities.push_back(model);
	}
	for (auto* object : _impl->objects->get()) {
		_impl->entities.push_back(object);
	}
	for (auto* place : _impl->places->get()) {
		_impl->entities.push_back(place);
	}
	emit entitiesUpdated();
}

} // namespace fsd

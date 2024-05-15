#include <lh/data/Project.hpp>

#include <QtCore/QFile>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QSaveFile>

#include <lh/data/Character.hpp>
#include <lh/data/Link.hpp>
#include <lh/data/Place.hpp>
#include <lh/data/UuidPointer.hpp>
#include <lh/io/Json.hpp>

#include "common/Tools.hpp"

namespace lh {

struct Project::Impl {
	UuidPointer<Place>* defaultPlace{ nullptr };
	QUrl path{};
	QList<Character*> characters{};
	QList<Link*> links{};
	QList<Place*> places{};

	template<class TClass>
	void loadList(Project* project, QList<TClass*>& list, const QString& key, const QJsonObject& json, void (Project::*signal)()) {
		list.clear();
		const auto& jsonArray = Json::toArray(key, json);
		for (const auto& jsonEntity : jsonArray) {
			assert(jsonEntity.isObject());
			auto* entity = new TClass(project);
			entity->load(jsonEntity.toObject());
			list.append(entity);
		}
		emit(project->*signal)();
	}

	template<class TClass>
	void saveList(const QList<TClass*>& list, const QString& key, QJsonObject& json) {
		QJsonArray jsonArray;
		for (auto* entity : list) {
			QJsonObject jsonEntity;
			entity->save(jsonEntity);
			jsonArray.append(jsonEntity);
		}
		json[key] = jsonArray;
	}
};

Project::Project(QObject* parent)
	: Entity(parent)
	, _impl{ std::make_unique<Impl>() } {
	_impl->defaultPlace = makePlacePointer(this, this);
}

Project::~Project() {}

void Project::reset() {
	Entity::reset();
	setDefaultPlace(nullptr);
	cleanCharacters();
	cleanLinks();
	cleanPlaces();
}

const QUrl& Project::path() const {
	return _impl->path;
}

void Project::setPath(const QUrl& path) {
	TOOLS_SETTER(Project, path);
}

Place* Project::defaultPlace() const {
	return (_impl->defaultPlace->valid()) ? _impl->defaultPlace->get() : nullptr;
}

void Project::setDefaultPlace(Place* defaultPlace) {
	if (_impl->defaultPlace->set(defaultPlace)) {
		emit defaultPlaceUpdated();
	}
}

const QList<Character*>& Project::characters() const {
	return _impl->characters;
}

void Project::setCharacters(const QList<Character*>& characters) {
	TOOLS_SETTER(Project, characters);
}

Character* Project::createCharacter() {
	TOOLS_CREATE_ENTITY(Project, characters);
}

void Project::removeCharacter(Character* character) {
	TOOLS_REMOVE_ENTITY(Project, character);
}

Character* Project::duplicateCharacter(Character* character) {
	TOOLS_DUPLICATE_ENTITY(Project, character);
}

void Project::cleanCharacters() {
	TOOLS_CLEAN_ENTITIES(Project, characters);
}

const QList<Link*>& Project::links() const {
	return _impl->links;
}

void Project::setLinks(const QList<Link*>& links) {
	TOOLS_SETTER(Project, links);
}

Link* Project::createLink() {
	TOOLS_CREATE_ENTITY(Project, links);
}

void Project::removeLink(Link* link) {
	TOOLS_REMOVE_ENTITY(Project, link);
}

Link* Project::duplicateLink(Link* link) {
	TOOLS_DUPLICATE_ENTITY(Project, link);
}

void Project::cleanLinks() {
	TOOLS_CLEAN_ENTITIES(Project, links);
}

const QList<Place*>& Project::places() const {
	return _impl->places;
}

void Project::setPlaces(const QList<Place*>& places) {
	TOOLS_SETTER(Project, places);
}

Place* Project::createPlace() {
	TOOLS_CREATE_ENTITY(Project, places);
}

void Project::removePlace(Place* place) {
	TOOLS_REMOVE_ENTITY(Project, place);
}

Place* Project::duplicatePlace(Place* place) {
	TOOLS_DUPLICATE_ENTITY(Project, place);
}

void Project::cleanPlaces() {
	TOOLS_CLEAN_ENTITIES(Project, places);
}

constexpr auto lDefaultPlaces = "defaultPlace";
constexpr auto lCharacters = "characters";
constexpr auto lLinks = "links";
constexpr auto lPlaces = "places";

void Project::load(const QUrl& url) {
	QFile file(Tools::toPath(url));
	if (!file.open(QIODevice::ReadOnly)) {
		// ERROR
		return;
	}
	setPath(url);

	// Read
	load(QJsonDocument::fromJson(file.readAll()).object());
}

void Project::load(const QJsonObject& json) {
	reset();
	Entity::load(json);

	_impl->defaultPlace->setUuid(Json::toUuid(Json::toValue(lDefaultPlaces, json)));
	emit defaultPlaceUpdated();

	_impl->loadList(this, _impl->characters, lCharacters, json, &Project::charactersUpdated);
	_impl->loadList(this, _impl->links, lLinks, json, &Project::linksUpdated);
	_impl->loadList(this, _impl->places, lPlaces, json, &Project::placesUpdated);
}

void Project::save(const QUrl& url) {
	QSaveFile file(Tools::toPath(url));
	if (!file.open(QIODevice::WriteOnly)) {
		// ERROR
		return;
	}
	setPath(url);

	// Write
	QJsonObject json;
	save(json);
	file.write(QJsonDocument(json).toJson());
	file.commit();
}

void Project::save(QJsonObject& json) const {
	Entity::save(json);
	json[lDefaultPlaces] = Json::fromUuid(_impl->defaultPlace->uuid());
	_impl->saveList(_impl->characters, lCharacters, json);
	_impl->saveList(_impl->links, lLinks, json);
	_impl->saveList(_impl->places, lPlaces, json);
}
} // namespace lh

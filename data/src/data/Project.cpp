#include <lh/data/Project.hpp>

#include <QtCore/QFile>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QSaveFile>

#include <lh/data/Character.hpp>
#include <lh/data/Place.hpp>
#include <lh/data/UuidPointer.hpp>
#include <lh/io/Json.hpp>

#include "common/Tools.hpp"

namespace lh {

struct Project::Impl {
	UuidPointer<Place> defaultPlace{};
	QUrl path{};
	QList<Character*> characters{};
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
	initPlacePointer(_impl->defaultPlace, this);
}

Project::~Project() {}

void Project::reset() {
	Entity::reset();
	setDefaultPlace(nullptr);
	cleanCharacters();
	cleanPlaces();
}

constexpr auto ldefaultplaces = "defaultplace";
constexpr auto lcharacters = "characters";
constexpr auto lplaces = "places";

void Project::load(const QUrl& url) {
	QFile file(Tools::toPath(url));
	if (!file.open(QIODevice::ReadOnly)) {
		// ERROR
		return;
	}
	setPath(url);

	// Read
	const auto& data = file.readAll();
	const auto& loadDoc = QJsonDocument::fromJson(data);
	const auto& json = loadDoc.object();

	// JSON
	reset();
	Entity::load(json);

	_impl->defaultPlace.setUuid(Json::toUuid(Json::toValue(ldefaultplaces, json)));
	emit defaultPlaceUpdated();

	_impl->loadList(this, _impl->characters, lcharacters, json, &Project::charactersUpdated);
	_impl->loadList(this, _impl->places, lplaces, json, &Project::placesUpdated);
}

void Project::save(const QUrl& url) {
	QSaveFile file(Tools::toPath(url));
	if (!file.open(QIODevice::WriteOnly)) {
		// ERROR
		return;
	}
	setPath(url);

	// JSON
	QJsonObject json;
	Entity::save(json);

	json[ldefaultplaces] = Json::fromUuid(_impl->defaultPlace.uuid());

	_impl->saveList(_impl->characters, lcharacters, json);
	_impl->saveList(_impl->places, lplaces, json);

	// Write
	const auto& data = QJsonDocument(json).toJson();
	file.write(data);
	file.commit();
}

const QUrl& Project::path() const {
	return _impl->path;
}

void Project::setPath(const QUrl& path) {
	TOOLS_SETTER(Project, path);
}

Place* Project::defaultPlace() const {
	return (_impl->defaultPlace.isNull()) ? nullptr : _impl->defaultPlace.get();
}

void Project::setDefaultPlace(Place* newPlace) {
	if (_impl->defaultPlace.set(newPlace)) {
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
} // namespace lh

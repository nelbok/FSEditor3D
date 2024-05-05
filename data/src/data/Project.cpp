#include <lh/data/Project.hpp>

#include <QtCore/QFile>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QSaveFile>
#include <QtCore/QUrl>

#include <lh/data/Place.hpp>
#include <lh/io/Json.hpp>

namespace lh {

namespace detail {
QString toPath(const QUrl& url) {
	assert(url.isValid());
	if (url.isLocalFile())
		return url.toLocalFile();
	else
		return url.toString();
}
} // namespace detail

Project::Project(QObject* parent)
	: Entity(this, parent) {
	_defaultPlace = makePlacePointer(this);
	Project::reset();
}

Project::~Project() {}

void Project::reset() {
	Entity::reset();
	cleanPlaces();
}

void Project::load(const QUrl& url) {
	QFile file(detail::toPath(url));
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

	_places.clear();
	const auto& jsonPlaces = Json::toArray("places", json);
	for (const auto& jsonPlace : jsonPlaces) {
		assert(jsonPlace.isObject());
		auto* place = new Place(this);
		place->load(jsonPlace.toObject());
		_places.append(place);
	}
	emit placesUpdated();
}

void Project::save(const QUrl& url) {
	QSaveFile file(detail::toPath(url));
	if (!file.open(QIODevice::WriteOnly)) {
		// ERROR
		return;
	}
	setPath(url);

	// JSON
	QJsonObject json;
	Entity::save(json);

	QJsonArray jsonPlaces;
	for (auto* place : _places) {
		QJsonObject jsonPlace;
		place->save(jsonPlace);
		jsonPlaces.append(jsonPlace);
	}
	json["places"] = jsonPlaces;

	// Write
	const auto& data = QJsonDocument(json).toJson();
	file.write(data);
	file.commit();
}

const QUrl& Project::path() const {
	return _path;
}

void Project::setPath(const QUrl& path) {
	if (_path != path) {
		_path = path;
		emit pathUpdated();
	}
}

Place* Project::defaultPlace() const {
	return (_defaultPlace.isNull()) ? nullptr : _defaultPlace.get();
}

void Project::setDefaultPlace(Place* newPlace) {
	assert(newPlace);
	if (_defaultPlace.uuid() != newPlace->uuid()) {
		_defaultPlace.setUuid(newPlace->uuid());
		emit defaultPlaceUpdated();
	}
}

const QList<Place*>& Project::places() const {
	return _places;
}

void Project::setPlaces(const QList<Place*>& places) {
	if (_places != places) {
		_places = places;
		emit placesUpdated();
	}
}

Place* Project::createPlace() {
	auto* place = new Place(this);
	_places.append(place);
	emit placesUpdated();
	return place;
}

void Project::removePlace(Place* place) {
	assert(place);
	assert(_places.contains(place));
	_places.removeAll(place);
	place->deleteLater();
	emit placesUpdated();
}

Place* Project::duplicatePlace(Place* oldPlace) {
	auto* newPlace = new Place(this);
	newPlace->copy(*oldPlace);
	newPlace->setName(newPlace->name() + "*");
	_places.append(newPlace);
	emit placesUpdated();
	return newPlace;
}

void Project::cleanPlaces() {
	for (auto* place : _places) {
		place->reset();
		place->deleteLater();
	}
	_places.clear();
	emit placesUpdated();
}

} // namespace lh

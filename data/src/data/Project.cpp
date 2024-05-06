#include <lh/data/Project.hpp>

#include <QtCore/QFile>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QSaveFile>
#include <QtCore/QUrl>

#include <lh/data/Place.hpp>
#include <lh/data/UuidPointer.hpp>
#include <lh/io/Json.hpp>

namespace lh {

struct Project::Impl {
	static QString toPath(const QUrl& url) {
		assert(url.isValid());
		if (url.isLocalFile())
			return url.toLocalFile();
		else
			return url.toString();
	}

	UuidPointer<Place> defaultPlace{};
	QUrl path{};
	QList<Place*> places{};
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
	cleanPlaces();
}

constexpr auto ldefaultplaces = "defaultplace";
constexpr auto lplaces = "places";

void Project::load(const QUrl& url) {
	QFile file(Impl::toPath(url));
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

	_impl->places.clear();
	const auto& jsonPlaces = Json::toArray(lplaces, json);
	for (const auto& jsonPlace : jsonPlaces) {
		assert(jsonPlace.isObject());
		auto* place = new Place(this);
		place->load(jsonPlace.toObject());
		_impl->places.append(place);
	}
	emit placesUpdated();
}

void Project::save(const QUrl& url) {
	QSaveFile file(Impl::toPath(url));
	if (!file.open(QIODevice::WriteOnly)) {
		// ERROR
		return;
	}
	setPath(url);

	// JSON
	QJsonObject json;
	Entity::save(json);

	json[ldefaultplaces] = Json::fromUuid(_impl->defaultPlace.uuid());

	QJsonArray jsonPlaces;
	for (auto* place : _impl->places) {
		QJsonObject jsonPlace;
		place->save(jsonPlace);
		jsonPlaces.append(jsonPlace);
	}
	json[lplaces] = jsonPlaces;

	// Write
	const auto& data = QJsonDocument(json).toJson();
	file.write(data);
	file.commit();
}

const QUrl& Project::path() const {
	return _impl->path;
}

void Project::setPath(const QUrl& path) {
	if (_impl->path != path) {
		_impl->path = path;
		emit pathUpdated();
	}
}

Place* Project::defaultPlace() const {
	return (_impl->defaultPlace.isNull()) ? nullptr : _impl->defaultPlace.get();
}

void Project::setDefaultPlace(Place* newPlace) {
	if (_impl->defaultPlace.set(newPlace)) {
		emit defaultPlaceUpdated();
	}
}

const QList<Place*>& Project::places() const {
	return _impl->places;
}

void Project::setPlaces(const QList<Place*>& places) {
	if (_impl->places != places) {
		_impl->places = places;
		emit placesUpdated();
	}
}

Place* Project::createPlace() {
	auto* place = new Place(this);
	place->reset();
	_impl->places.append(place);
	emit placesUpdated();
	return place;
}

void Project::removePlace(Place* place) {
	assert(place);
	assert(_impl->places.contains(place));
	_impl->places.removeAll(place);
	place->deleteLater();
	emit placesUpdated();
}

Place* Project::duplicatePlace(Place* oldPlace) {
	auto* newPlace = new Place(this);
	newPlace->copy(*oldPlace);
	newPlace->setName(newPlace->name() + "*");
	_impl->places.append(newPlace);
	emit placesUpdated();
	return newPlace;
}

void Project::cleanPlaces() {
	for (auto* place : _impl->places) {
		place->reset();
		place->deleteLater();
	}
	_impl->places.clear();
	emit placesUpdated();
}
} // namespace lh

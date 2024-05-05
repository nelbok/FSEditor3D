#include <lh/data/Placement.hpp>

#include <lh/data/Place.hpp>
#include <lh/io/Json.hpp>

namespace lh {
Placement::Placement(Project* project)
	: Entity(project) {
	// Need PIMPL
	//_place = makePlacePointer(project);
	Placement::reset();
}

Placement::~Placement() {}

void Placement::reset() {
	Entity::reset();
	setPosition({ 0, 0, 0 });
	setRotation({ 0, 0, 0 });
	setPlace(nullptr);
}

void Placement::copy(const Placement& placement) {
	Entity::copy(placement);
	setPosition(placement.position());
	setRotation(placement.rotation());
}

const QVector3D& Placement::position() const {
	return _position;
}

void Placement::setPosition(const QVector3D& position) {
	if (_position != position) {
		_position = position;
		emit positionUpdated();
	}
}

const QVector3D& Placement::rotation() const {
	return _rotation;
}

void Placement::setRotation(const QVector3D& rotation) {
	if (_rotation != rotation) {
		_rotation = rotation;
		emit rotationUpdated();
	}
}

Place* Placement::place() const {
	return (_place.isNull()) ? nullptr : _place.get();
}

void Placement::setPlace(Place* newPlace) {
	if (_place.set(newPlace)) {
		emit placeUpdated();
	}
}

constexpr auto lposition = "position";
constexpr auto lrotation = "rotation";
constexpr auto lplace = "place";

void Placement::load(const QJsonObject& json) {
	Entity::load(json);
	setPosition(Json::toVector3D(Json::toObject(lposition, json)));
	setRotation(Json::toVector3D(Json::toObject(lrotation, json)));
	_place.setUuid(Json::toUuid(Json::toValue(lplace, json)));
	emit placeUpdated();
}

void Placement::save(QJsonObject& json) const {
	Entity::save(json);
	json[lposition] = Json::fromVector3D(_position);
	json[lrotation] = Json::fromVector3D(_rotation);
	json[lplace] = Json::fromUuid(_place.uuid());
}
} // namespace lh

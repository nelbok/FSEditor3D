#include <lh/data/Placement.hpp>

#include <lh/data/Place.hpp>
#include <lh/data/Project.hpp>
#include <lh/data/UuidPointer.hpp>
#include <lh/io/Json.hpp>

#include "common/Tools.hpp"

namespace lh {
struct Placement::Impl {
	QVector3D position{};
	QVector3D rotation{};
	UuidPointer<Place> place{};
};

Placement::Placement(Project* project)
	: Entity(project)
	, _impl{ std::make_unique<Impl>() } {
	initPlacePointer(_impl->place, project);
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
	setPlace(placement.place());
}

const QVector3D& Placement::position() const {
	return _impl->position;
}

void Placement::setPosition(const QVector3D& position) {
	TOOLS_SETTER(Placement, position);
}

const QVector3D& Placement::rotation() const {
	return _impl->rotation;
}

void Placement::setRotation(const QVector3D& rotation) {
	TOOLS_SETTER(Placement, rotation);
}

Place* Placement::place() const {
	return (_impl->place.isNull()) ? nullptr : _impl->place.get();
}

void Placement::setPlace(Place* newPlace) {
	if (_impl->place.set(newPlace)) {
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
	_impl->place.setUuid(Json::toUuid(Json::toValue(lplace, json)));
	emit placeUpdated();
}

void Placement::save(QJsonObject& json) const {
	Entity::save(json);
	json[lposition] = Json::fromVector3D(_impl->position);
	json[lrotation] = Json::fromVector3D(_impl->rotation);
	json[lplace] = Json::fromUuid(_impl->place.uuid());
}
} // namespace lh

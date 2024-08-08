#include <fsd/data/Placement.hpp>

#include <fsd/data/Place.hpp>
#include <fsd/data/Project.hpp>
#include <fsd/data/UuidPointer.hpp>
#include <fsd/io/Json.hpp>

#include "common/Accessors.hpp"

namespace fsd {
struct Placement::Impl {
	QVector3D position{};
	QVector3D rotation{};
	UuidPointer<Place>* place{ nullptr };
};

Placement::Placement(Project* project)
	: Shape(project)
	, _impl{ std::make_unique<Impl>() } {
	_impl->place = makePlacePointer(project, this);
}

Placement::~Placement() {}

void Placement::reset() {
	Shape::reset();
	setPosition({ 0, 0, 0 });
	setRotation({ 0, 0, 0 });
	setPlace(nullptr);
}

void Placement::copy(const Placement& placement) {
	Shape::copy(placement);
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
	return (_impl->place->valid()) ? _impl->place->get() : nullptr;
}

void Placement::setPlace(Place* place) {
	if (_impl->place->set(place)) {
		emit placeUpdated();
	}
}

constexpr auto lPosition = "position";
constexpr auto lRotation = "rotation";
constexpr auto lPlace = "place";

void Placement::load(const QJsonObject& json) {
	Shape::load(json);
	setPosition(Json::toVector3D(Json::toObject(lPosition, json)));
	setRotation(Json::toVector3D(Json::toObject(lRotation, json)));
	_impl->place->setUuid(Json::toUuid(Json::toValue(lPlace, json)));
	emit placeUpdated();
}

void Placement::save(QJsonObject& json) const {
	Shape::save(json);
	json[lPosition] = Json::fromVector3D(_impl->position);
	json[lRotation] = Json::fromVector3D(_impl->rotation);
	json[lPlace] = Json::fromUuid(_impl->place->uuid());
}
} // namespace fsd

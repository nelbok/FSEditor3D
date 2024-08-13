#include <fsd/data/Geometry.hpp>

#include <fsd/io/Json.hpp>

#include "common/Accessors.hpp"

namespace fsd {
struct Geometry::Impl {
	QVector3D position{};
	QVector3D rotation{};
	QVector3D scale{};
};

Geometry::Geometry(QObject* parent)
	: Entity(parent)
	, _impl{ std::make_unique<Impl>() } {
}

Geometry::~Geometry() {}

void Geometry::reset() {
	Entity::reset();
	setPosition({ 0, 0, 0 });
	setRotation({ 0, 0, 0 });
	setScale({ 1, 1, 1 });
}

void Geometry::copy(const Geometry& geometry) {
	Entity::copy(geometry);
	setPosition(geometry.position());
	setRotation(geometry.rotation());
	setScale(geometry.scale());
}

const QVector3D& Geometry::position() const {
	return _impl->position;
}

void Geometry::setPosition(const QVector3D& position) {
	TOOLS_SETTER(Geometry, position);
}

const QVector3D& Geometry::rotation() const {
	return _impl->rotation;
}

void Geometry::setRotation(const QVector3D& rotation) {
	TOOLS_SETTER(Geometry, rotation);
}

const QVector3D& Geometry::scale() const {
	return _impl->scale;
}

void Geometry::setScale(const QVector3D& scale) {
	TOOLS_SETTER(Geometry, scale);
}

constexpr auto lPosition = "position";
constexpr auto lRotation = "rotation";
constexpr auto lScale = "scale";

void Geometry::load(const QJsonObject& json) {
	Entity::load(json);
	setPosition(Json::toVector3D(Json::toObject(lPosition, json)));
	setRotation(Json::toVector3D(Json::toObject(lRotation, json)));
	setScale(Json::toVector3D(Json::toObject(lScale, json)));
}

void Geometry::save(QJsonObject& json) const {
	Entity::save(json);
	json[lPosition] = Json::fromVector3D(_impl->position);
	json[lRotation] = Json::fromVector3D(_impl->rotation);
	json[lScale] = Json::fromVector3D(_impl->scale);
}
} // namespace fsd

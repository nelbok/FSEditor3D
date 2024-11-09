#include <fsd/data/Geometry.hpp>

#include <fsd/io/Format.hpp>
#include <fsd/io/Json.hpp>

#include "common/Accessors.hpp"

namespace fsd {
struct Geometry::Impl {
	QVector3D localPosition{};
	QVector3D localRotation{};
	QVector3D localScale{};
};

Geometry::Geometry(fsd::Project* project, QObject* parent)
	: Entity(project, parent)
	, _impl{ std::make_unique<Impl>() } {
	QObject::connect(this, &Geometry::localPositionUpdated, this, &Geometry::globalPositionUpdated);
	QObject::connect(this, &Geometry::localRotationUpdated, this, &Geometry::globalRotationUpdated);
	QObject::connect(this, &Geometry::localScaleUpdated, this, &Geometry::globalScaleUpdated);
}

Geometry::~Geometry() = default;

void Geometry::reset() {
	Entity::reset();
	setLocalPosition({ 0, 0, 0 });
	setLocalRotation({ 0, 0, 0 });
	setLocalScale({ 1, 1, 1 });
}

void Geometry::copy(const Geometry& geometry) {
	Entity::copy(geometry);
	setLocalPosition(geometry.localPosition());
	setLocalRotation(geometry.localRotation());
	setLocalScale(geometry.localScale());
}

const QVector3D& Geometry::localPosition() const {
	return _impl->localPosition;
}

void Geometry::setLocalPosition(const QVector3D& localPosition) {
	TOOLS_SETTER(Geometry, localPosition);
}

const QVector3D& Geometry::localRotation() const {
	return _impl->localRotation;
}

void Geometry::setLocalRotation(const QVector3D& localRotation) {
	TOOLS_SETTER(Geometry, localRotation);
}

const QVector3D& Geometry::localScale() const {
	return _impl->localScale;
}

void Geometry::setLocalScale(const QVector3D& localScale) {
	TOOLS_SETTER(Geometry, localScale);
}

QVector3D Geometry::globalPosition() const {
	return _impl->localPosition;
}

QVector3D Geometry::globalRotation() const {
	return _impl->localRotation;
}

QVector3D Geometry::globalScale() const {
	return _impl->localScale;
}

void Geometry::load(const QJsonObject& json) {
	Entity::load(json);
	setLocalPosition(Json::toVector3D(Json::toObject(Format::lPosition, json)));
	setLocalRotation(Json::toVector3D(Json::toObject(Format::lRotation, json)));
	setLocalScale(Json::toVector3D(Json::toObject(Format::lScale, json)));
}

void Geometry::save(QJsonObject& json) const {
	Entity::save(json);
	json[Format::lPosition] = Json::fromVector3D(_impl->localPosition);
	json[Format::lRotation] = Json::fromVector3D(_impl->localRotation);
	json[Format::lScale] = Json::fromVector3D(_impl->localScale);
}
} // namespace fsd

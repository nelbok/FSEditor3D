#include <fsd/data/EntryPoint.hpp>

#include <fsd/data/Place.hpp>
#include <fsd/data/Project.hpp>
#include <fsd/data/UuidPointer.hpp>

namespace fsd {
struct EntryPoint::Impl {
	QVector3D position{};
	float rotation{};
	UuidPointer<Place>* place{ nullptr };
};

EntryPoint::EntryPoint(Project* project)
	: Entity(project, project)
	, _impl{ std::make_unique<Impl>() } {
	setObjectName("EntryPoint");
	_impl->place = makePlacePointer(project, this);
}

EntryPoint::~EntryPoint() = default;

void EntryPoint::reset() {
	Entity::reset();
	setPosition({ 0.f, 0.f, 0.f });
	setRotation(0.f);
	setPlace(nullptr);
}

void EntryPoint::copy(const EntryPoint& entryPoint) {
	Entity::copy(entryPoint);
	setPosition(entryPoint.position());
	setRotation(entryPoint.rotation());
	setPlace(entryPoint.place());
}

const QVector3D& EntryPoint::position() const {
	return _impl->position;
}

void EntryPoint::setPosition(const QVector3D& position) {
	TOOLS_SETTER(EntryPoint, position);
}

Place* EntryPoint::place() const {
	return (_impl->place->valid()) ? _impl->place->get() : nullptr;
}

void EntryPoint::setPlace(Place* place) {
	if (_impl->place->set(place)) {
		emit placeUpdated();
	}
}

float EntryPoint::rotation() const {
	return _impl->rotation;
}

void EntryPoint::setRotation(float rotation) {
	TOOLS_SETTER(EntryPoint, rotation);
}

EntryPoint::Type EntryPoint::type() const {
	return Type::EntryPoint;
}

void EntryPoint::load(const QJsonObject& json) {
	Entity::load(json);
	setPosition(Json::toVector3D(objectName(), Format::lPosition, json));
	setRotation(static_cast<float>(Json::toDouble(objectName(), Format::lRotation, json)));
	_impl->place->setUuid(Json::toUuid(objectName(), Format::lPlace, json));
	emit placeUpdated();
}

void EntryPoint::save(QJsonObject& json) const {
	Entity::save(json);
	json[Format::lPosition] = Json::fromVector3D(_impl->position);
	json[Format::lRotation] = _impl->rotation;
	json[Format::lPlace] = Json::fromUuid(_impl->place->uuid());
}
} // namespace fsd

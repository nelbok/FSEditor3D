#include <fsd/data/Placement.hpp>

#include <fsd/data/Place.hpp>
#include <fsd/data/Project.hpp>
#include <fsd/data/UuidPointer.hpp>

namespace fsd {
struct Placement::Impl {
	UuidPointer<Place>* place{ nullptr };
};

Placement::Placement(Project* project, QObject* parent)
	: Shape(project, parent)
	, _impl{ std::make_unique<Impl>() } {
	setObjectName("Placement");
	_impl->place = makePlacePointer(project, this);
}

Placement::~Placement() = default;

void Placement::reset() {
	Shape::reset();
	setPlace(nullptr);
}

void Placement::copy(const Placement& placement) {
	Shape::copy(placement);
	setPlace(placement.place());
}

Place* Placement::place() const {
	return (_impl->place->valid()) ? _impl->place->get() : nullptr;
}

void Placement::setPlace(Place* place) {
	if (_impl->place->set(place)) {
		emit placeUpdated();
	}
}

void Placement::load(const QJsonObject& json) {
	Shape::load(json);
	_impl->place->setUuid(Json::toUuid(objectName(), Format::lPlace, json));
	emit placeUpdated();
}

void Placement::save(QJsonObject& json) const {
	Shape::save(json);
	json[Format::lPlace] = Json::fromUuid(_impl->place->uuid());
}
} // namespace fsd

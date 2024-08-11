#include <fsd/data/Place.hpp>

#include <fsd/data/Project.hpp>

namespace fsd {
struct Place::Impl {};

Place::Place(Project* project)
	: Shape(project)
	, _impl{ std::make_unique<Impl>() } {}

Place::~Place() {}

void Place::reset() {
	Shape::reset();
}

void Place::copy(const Place& place) {
	Shape::copy(place);
}

Place::Type Place::type() const {
	return Type::Place;
}

void Place::load(const QJsonObject& json) {
	Shape::load(json);
}

void Place::save(QJsonObject& json) const {
	Shape::save(json);
}
} // namespace fsd

#include <fsd/data/Place.hpp>

#include <fsd/data/Project.hpp>

namespace fsd {
struct Place::Impl {};

Place::Place(Project* project)
	: Object(project)
	, _impl{ std::make_unique<Impl>() } {}

Place::~Place() {}

void Place::reset() {
	Object::reset();
}

void Place::copy(const Place& place) {
	Object::copy(place);
}

void Place::load(const QJsonObject& json) {
	Object::load(json);
}

void Place::save(QJsonObject& json) const {
	Object::save(json);
}
} // namespace fsd

#include <lh/data/Place.hpp>

#include <lh/data/Project.hpp>

namespace lh {
struct Place::Impl {};

Place::Place(Project* project)
	: Entity(project)
	, _impl{ std::make_unique<Impl>() } {}

Place::~Place() {}

void Place::reset() {
	Entity::reset();
}

void Place::copy(const Place& place) {
	Entity::copy(place);
}

void Place::load(const QJsonObject& json) {
	Entity::load(json);
}

void Place::save(QJsonObject& json) const {
	Entity::save(json);
}
} // namespace lh

#include <lh/data/Place.hpp>

namespace lh {
Place::Place(Project* project)
	: Entity(project) {
	reset();
}

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

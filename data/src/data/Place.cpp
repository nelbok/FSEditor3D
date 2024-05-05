#include <lh/data/Place.hpp>

namespace lh {
Place::Place(Project* project)
	: Entity(project) {
	reset();
}

Place::~Place() {}

void Place::reset() {
}

void Place::copy(const Place& entity) {
	Entity::copy(entity);
}

void Place::load(const QJsonObject& json) {
	Entity::load(json);
}

void Place::save(QJsonObject& json) const {
	Entity::save(json);
}

} // namespace lh

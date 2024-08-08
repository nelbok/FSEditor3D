#include <fsd/data/Object.hpp>

#include <fsd/io/Json.hpp>

namespace fsd {
struct Object::Impl {};

Object::Object(Project* project)
	: Placement(project)
	, _impl{ std::make_unique<Impl>() } {}

Object::~Object() {}

void Object::reset() {
	Placement::reset();
}

void Object::copy(const Object& object) {
	Placement::copy(object);
}

void Object::load(const QJsonObject& json) {
	Placement::load(json);
}

void Object::save(QJsonObject& json) const {
	Placement::save(json);
}
} // namespace fsd

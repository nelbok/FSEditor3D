#include <fsd/data/Object.hpp>

#include <fsd/data/Project.hpp>
#include <fsd/io/Json.hpp>

namespace fsd {
struct Object::Impl {};

Object::Object(Project* project)
	: Placement(project, project)
	, _impl{ std::make_unique<Impl>() } {
	setObjectName("Object");
}

Object::~Object() = default;

void Object::reset() {
	Placement::reset();
}

void Object::copy(const Object& object) {
	Placement::copy(object);
}

Object::Type Object::type() const {
	return Type::Object;
}

void Object::load(const QJsonObject& json) {
	Placement::load(json);
}

void Object::save(QJsonObject& json) const {
	Placement::save(json);
}
} // namespace fsd

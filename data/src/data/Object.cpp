#include <fsd/data/Object.hpp>

#include <fsd/data/Model.hpp>
#include <fsd/data/Project.hpp>
#include <fsd/data/UuidPointer.hpp>
#include <fsd/io/Json.hpp>

namespace fsd {
struct Object::Impl {
	UuidPointer<Model>* model{ nullptr };
};

Object::Object(Project* project)
	: Entity(project)
	, _impl{ std::make_unique<Impl>() } {
	_impl->model = makeModelPointer(project, this);
}

Object::~Object() {}

void Object::reset() {
	Entity::reset();
	setModel(nullptr);
}

void Object::copy(const Object& object) {
	Entity::copy(object);
	setModel(object.model());
}

Model* Object::model() const {
	return (_impl->model->valid()) ? _impl->model->get() : nullptr;
}

void Object::setModel(Model* model) {
	if (_impl->model->set(model)) {
		emit modelUpdated();
	}
}

constexpr auto lModel = "model";

void Object::load(const QJsonObject& json) {
	Entity::load(json);
	_impl->model->setUuid(Json::toUuid(Json::toValue(lModel, json)));
	emit modelUpdated();
}

void Object::save(QJsonObject& json) const {
	Entity::save(json);
	json[lModel] = Json::fromUuid(_impl->model->uuid());
}
} // namespace fsd

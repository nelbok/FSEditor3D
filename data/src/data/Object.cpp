#include <lh/data/Object.hpp>

#include <lh/data/Model.hpp>
#include <lh/data/Project.hpp>
#include <lh/data/UuidPointer.hpp>
#include <lh/io/Json.hpp>

namespace lh {
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

void Object::setModel(Model* link) {
	if (_impl->model->set(link)) {
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
} // namespace lh

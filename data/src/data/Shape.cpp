#include <fsd/data/Shape.hpp>

#include <fsd/data/Model.hpp>
#include <fsd/data/Project.hpp>
#include <fsd/data/UuidPointer.hpp>
#include <fsd/io/Json.hpp>

namespace fsd {
struct Shape::Impl {
	UuidPointer<Model>* model{ nullptr };
};

Shape::Shape(Project* project)
	: Geometry(project)
	, _impl{ std::make_unique<Impl>() } {
	_impl->model = makeModelPointer(project, this);
}

Shape::~Shape() {}

void Shape::reset() {
	Geometry::reset();
	setModel(nullptr);
}

void Shape::copy(const Shape& shape) {
	Geometry::copy(shape);
	setModel(shape.model());
}

Model* Shape::model() const {
	return (_impl->model->valid()) ? _impl->model->get() : nullptr;
}

void Shape::setModel(Model* model) {
	if (_impl->model->set(model)) {
		emit modelUpdated();
	}
}

constexpr auto lModel = "model";

void Shape::load(const QJsonObject& json) {
	Geometry::load(json);
	_impl->model->setUuid(Json::toUuid(Json::toValue(lModel, json)));
	emit modelUpdated();
}

void Shape::save(QJsonObject& json) const {
	Geometry::save(json);
	json[lModel] = Json::fromUuid(_impl->model->uuid());
}
} // namespace fsd

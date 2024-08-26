#include <fsd/data/Shape.hpp>

#include <fsd/data/Model.hpp>
#include <fsd/data/Project.hpp>
#include <fsd/data/UuidPointer.hpp>
#include <fsd/io/Format.hpp>
#include <fsd/io/Json.hpp>

namespace fsd {
struct Shape::Impl {
	UuidPointer<Model>* model{ nullptr };
};

Shape::Shape(Project* project, QObject* parent)
	: Geometry(project, parent)
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
	// FIXME: Make it an exception
	assert(!model || (model->modelType() == Model::ModelType::Link && type() == Type::Link) || (model->modelType() == Model::ModelType::Object && type() == Type::Object)
				 || (model->modelType() == Model::ModelType::Place && type() == Type::Place));

	auto* oldModel = this->model();
	if (_impl->model->set(model)) {
		if (oldModel) {
			QObject::disconnect(oldModel, &Model::globalPositionUpdated, this, &Shape::globalPositionUpdated);
			QObject::disconnect(oldModel, &Model::globalRotationUpdated, this, &Shape::globalRotationUpdated);
			QObject::disconnect(oldModel, &Model::globalScaleUpdated, this, &Shape::globalScaleUpdated);
		}
		if (model) {
			QObject::connect(model, &Model::globalPositionUpdated, this, &Shape::globalPositionUpdated);
			QObject::connect(model, &Model::globalRotationUpdated, this, &Shape::globalRotationUpdated);
			QObject::connect(model, &Model::globalScaleUpdated, this, &Shape::globalScaleUpdated);
		}
		emit modelUpdated();
	}
}

QVector3D Shape::globalPosition() const {
	if (auto* model = this->model())
		return Geometry::globalPosition() + model->globalPosition();
	return Geometry::globalPosition();
}

QVector3D Shape::globalRotation() const {
	if (auto* model = this->model())
		return Geometry::globalRotation() + model->globalRotation();
	return Geometry::globalRotation();
}

QVector3D Shape::globalScale() const {
	if (auto* model = this->model())
		return Geometry::globalScale() * model->globalScale();
	return Geometry::globalScale();
}

void Shape::load(const QJsonObject& json) {
	Geometry::load(json);
	if (_impl->model->setUuid(Json::toUuid(Json::toValue(Format::lModel, json)))) {
		auto* model = _impl->model->get();
		assert(model);
		QObject::connect(model, &Model::globalPositionUpdated, this, &Shape::globalPositionUpdated);
		QObject::connect(model, &Model::globalRotationUpdated, this, &Shape::globalRotationUpdated);
		QObject::connect(model, &Model::globalScaleUpdated, this, &Shape::globalScaleUpdated);
	}
	emit modelUpdated();
}

void Shape::save(QJsonObject& json) const {
	Geometry::save(json);
	json[Format::lModel] = Json::fromUuid(_impl->model->uuid());
}
} // namespace fsd

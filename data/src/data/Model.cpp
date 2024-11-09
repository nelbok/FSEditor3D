#include <fsd/data/Model.hpp>

#include <fsd/data/Project.hpp>
#include <fsd/io/Format.hpp>
#include <fsd/io/Json.hpp>

#include "common/Accessors.hpp"

namespace fsd {
struct Model::Impl {
	QUrl sourcePath{};
	QString qmlName{};
	ModelType modelType{};
};

Model::Model(Project* project)
	: Geometry(project, project)
	, _impl{ std::make_unique<Impl>() } {
	QObject::connect(project, &Project::globalPositionUpdated, this, &Model::globalPositionUpdated);
	QObject::connect(project, &Project::globalRotationUpdated, this, &Model::globalRotationUpdated);
	QObject::connect(project, &Project::globalScaleUpdated, this, &Model::globalScaleUpdated);
}

Model::~Model() = default;

void Model::reset() {
	Geometry::reset();
	setSourcePath({});
	setQmlName({});
}

void Model::copy(const Model& model) {
	Geometry::copy(model);
	setSourcePath(model.sourcePath());
	setQmlName(model.qmlName());
	setModelType(model.modelType());
}

const QUrl& Model::sourcePath() const {
	return _impl->sourcePath;
}

void Model::setSourcePath(const QUrl& sourcePath) {
	TOOLS_SETTER(Model, sourcePath);
}

const QString& Model::qmlName() const {
	return _impl->qmlName;
}

void Model::setQmlName(const QString& qmlName) {
	TOOLS_SETTER(Model, qmlName);
}

Model::ModelType Model::modelType() const {
	return _impl->modelType;
}

void Model::setModelType(ModelType modelType) {
	// FIXME: Make it an exception
	assert(this->modelType() == modelType || !hasRef());
	TOOLS_SETTER(Model, modelType);
}

Model::Type Model::type() const {
	return Type::Model;
}

QVector3D Model::globalPosition() const {
	return Geometry::globalPosition() + project()->globalPosition();
}

QVector3D Model::globalRotation() const {
	return Geometry::globalRotation() + project()->globalRotation();
}

QVector3D Model::globalScale() const {
	return Geometry::globalScale() * project()->globalScale();
}

void Model::load(const QJsonObject& json) {
	Geometry::load(json);
	setSourcePath(Json::toUrl(Json::toValue(Format::lSourcePath, json)));
	setQmlName(Json::toString(Format::lQmlName, json));
	setModelType(static_cast<Model::ModelType>(Json::toInt(Format::lModelType, json)));
}

void Model::save(QJsonObject& json) const {
	Geometry::save(json);
	json[Format::lSourcePath] = Json::fromUrl(_impl->sourcePath);
	json[Format::lQmlName] = _impl->qmlName;
	json[Format::lModelType] = static_cast<int>(_impl->modelType);
}
} // namespace fsd

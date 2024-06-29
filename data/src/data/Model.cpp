#include <fsd/data/Model.hpp>

#include <fsd/data/Project.hpp>
#include <fsd/io/Json.hpp>

#include "common/Accessors.hpp"

namespace fsd {
struct Model::Impl {
	QUrl sourcePath{};
	QString qmlName{};
	Type type{};
};

Model::Model(Project* project)
	: Entity(project)
	, _impl{ std::make_unique<Impl>() } {
}

Model::~Model() {}

void Model::reset() {
	Entity::reset();
	setSourcePath({});
	setQmlName({});
	setType(Type::Place);
}

void Model::copy(const Model& model) {
	Entity::copy(model);
	setSourcePath(model.sourcePath());
	setQmlName(model.qmlName());
	setType(model.type());
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

Model::Type Model::type() const {
	return _impl->type;
}

void Model::setType(Type type) {
	TOOLS_SETTER(Model, type);
}

constexpr auto lSourcePath = "sourcePath";
constexpr auto lQmlName = "qmlName";
constexpr auto lType = "type";

void Model::load(const QJsonObject& json) {
	Entity::load(json);
	setSourcePath(Json::toUrl(Json::toValue(lSourcePath, json)));
	setQmlName(Json::toString(lQmlName, json));
	setType(static_cast<Model::Type>(Json::toInt(lType, json)));
}

void Model::save(QJsonObject& json) const {
	Entity::save(json);
	json[lSourcePath] = Json::fromUrl(_impl->sourcePath);
	json[lQmlName] = _impl->qmlName;
	json[lType] = static_cast<int>(_impl->type);
}
} // namespace fsd

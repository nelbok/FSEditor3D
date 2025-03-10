#include <fse/models/ModelModel.hpp>

#include <fsd/data/Container.hpp>
#include <fsd/data/Model.hpp>
#include <fsd/data/Project.hpp>

namespace fse {

ModelModel::ModelModel(fsd::Project* project, QObject* parent)
	: EntityModel(project, parent) {}

ModelModel::~ModelModel() = default;

void ModelModel::initDatas() {
	assert(_project);
	QObject::connect(_project, &fsd::Project::modelsUpdated, this, &ModelModel::updateDatas);
}

QHash<int, QByteArray> ModelModel::roleNames() const {
	QHash<int, QByteArray> roles = EntityModel::roleNames();
	auto i = static_cast<int>(roles.size());
	roles[i + 1] = "modelType";
	return roles;
}

void ModelModel::updateDatas() {
	assert(_project);
	fillDatas(_project->models());
}

void ModelModel::disconnectData(fsd::Entity* entity) {
	EntityModel::disconnectData(entity);
	const auto* model = qobject_cast<fsd::Model*>(entity);
	QObject::disconnect(model, &fsd::Model::modelTypeUpdated, this, &ModelModel::sortDatas);
}

void ModelModel::connectData(fsd::Entity* entity) {
	EntityModel::connectData(entity);
	const auto* model = qobject_cast<fsd::Model*>(entity);
	QObject::connect(model, &fsd::Model::modelTypeUpdated, this, &ModelModel::sortDatas);
}
} // namespace fse

#include "ModelModel.hpp"

#include <lh/data/Model.hpp>
#include <lh/data/Project.hpp>

namespace lhe {

ModelModel::ModelModel(lh::Project* project, QObject* parent)
	: EntityModel(project, parent) {}

ModelModel::~ModelModel() {}

void ModelModel::initDatas() {
	assert(_project);
	connect(_project, &lh::Project::modelsUpdated, this, &ModelModel::updateDatas);
}

QHash<int, QByteArray> ModelModel::roleNames() const {
	QHash<int, QByteArray> roles = EntityModel::roleNames();
	qsizetype i = roles.size();
	roles[i + 1] = "type";
	return roles;
}

void ModelModel::updateDatas() {
	assert(_project);
	fillDatas(_project->models());
}

void ModelModel::disconnectData(lh::Entity* entity) {
	auto* model = qobject_cast<lh::Model*>(entity);
	disconnect(model, &lh::Model::typeUpdated, this, &ModelModel::sortDatas);
}

void ModelModel::connectData(lh::Entity* entity) {
	auto* model = qobject_cast<lh::Model*>(entity);
	connect(model, &lh::Model::typeUpdated, this, &ModelModel::sortDatas);
}
} // namespace lhe

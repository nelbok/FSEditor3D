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

void ModelModel::updateDatas() {
	assert(_project);
	fillDatas(_project->models());
}
} // namespace lhe

#include <fse/models/EntryPointModel.hpp>

#include <fsd/data/Container.hpp>
#include <fsd/data/EntryPoint.hpp>
#include <fsd/data/Project.hpp>

namespace fse {

EntryPointModel::EntryPointModel(fsd::Project* project, QObject* parent)
	: EntityModel(project, parent) {}

EntryPointModel::~EntryPointModel() = default;

void EntryPointModel::initDatas() {
	assert(_project);
	QObject::connect(_project, &fsd::Project::entryPointsUpdated, this, &EntryPointModel::updateDatas);
}

void EntryPointModel::updateDatas() {
	assert(_project);
	fillDatas(_project->entryPoints());
}

} // namespace fse

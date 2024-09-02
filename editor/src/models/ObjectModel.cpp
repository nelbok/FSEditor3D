#include <fse/models/ObjectModel.hpp>

#include <fsd/data/Object.hpp>
#include <fsd/data/Project.hpp>

namespace fse {

ObjectModel::ObjectModel(fsd::Project* project, QObject* parent)
	: EntityModel(project, parent) {}

ObjectModel::~ObjectModel() {}

void ObjectModel::initDatas() {
	assert(_project);
	QObject::connect(_project, &fsd::Project::objectsUpdated, this, &ObjectModel::updateDatas);
}

void ObjectModel::updateDatas() {
	assert(_project);
	fillDatas(_project->objects());
}

} // namespace fse

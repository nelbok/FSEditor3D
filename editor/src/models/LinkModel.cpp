#include <fse/models/LinkModel.hpp>

#include <fsd/data/Link.hpp>
#include <fsd/data/Project.hpp>

namespace fse {

LinkModel::LinkModel(fsd::Project* project, QObject* parent)
	: EntityModel(project, parent) {}

LinkModel::~LinkModel() = default;

void LinkModel::initDatas() {
	assert(_project);
	QObject::connect(_project, &fsd::Project::linksUpdated, this, &LinkModel::updateDatas);
}

void LinkModel::updateDatas() {
	assert(_project);
	fillDatas(_project->links());
}

} // namespace fse

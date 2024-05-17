#include "LinkModel.hpp"

#include <lh/data/Link.hpp>
#include <lh/data/Project.hpp>

namespace lhe {

LinkModel::LinkModel(lh::Project* project, QObject* parent)
	: EntityModel(project, parent) {}

LinkModel::~LinkModel() {}

void LinkModel::initDatas() {
	assert(_project);
	connect(_project, &lh::Project::linksUpdated, this, &LinkModel::updateDatas);
}

void LinkModel::updateDatas() {
	assert(_project);
	fillDatas(_project->links());
}

} // namespace lhe

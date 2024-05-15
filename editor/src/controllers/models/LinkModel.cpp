#include "LinkModel.hpp"

#include <lh/data/Link.hpp>
#include <lh/data/Project.hpp>

namespace lhe {

LinkModel::LinkModel(QObject* parent)
	: EntityModel(parent) {}

LinkModel::~LinkModel() {}

void LinkModel::init(lh::Project* project) {
	assert(project);
	connect(project, &lh::Project::linksUpdated, this, [this, project]() {
		updateDatas(project->links());
	});
	updateDatas(project->links());
}

} // namespace lhe

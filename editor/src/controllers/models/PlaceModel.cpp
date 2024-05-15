#include "PlaceModel.hpp"

#include <lh/data/Place.hpp>
#include <lh/data/Project.hpp>

namespace lhe {

PlaceModel::PlaceModel(QObject* parent)
	: EntityModel(parent) {}

PlaceModel::~PlaceModel() {}

void PlaceModel::init(lh::Project* project) {
	assert(project);
	connect(project, &lh::Project::placesUpdated, this, [this, project]() {
		updateDatas(project->places());
	});
	updateDatas(project->places());
}

} // namespace lhe

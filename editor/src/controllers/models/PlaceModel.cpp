#include "PlaceModel.hpp"

#include <lh/data/Place.hpp>
#include <lh/data/Project.hpp>

namespace lhe {

PlaceModel::PlaceModel(lh::Project* project, QObject* parent)
	: EntityModel(project, parent) {}

PlaceModel::~PlaceModel() {}

void PlaceModel::initDatas() {
	assert(_project);
	connect(_project, &lh::Project::placesUpdated, this, &PlaceModel::updateDatas);
}

void PlaceModel::updateDatas() {
	assert(_project);
	fillDatas(_project->places());
}
} // namespace lhe

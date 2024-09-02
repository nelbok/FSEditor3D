#include <fse/models/PlaceModel.hpp>

#include <fsd/data/Place.hpp>
#include <fsd/data/Project.hpp>

namespace fse {

PlaceModel::PlaceModel(fsd::Project* project, QObject* parent)
	: EntityModel(project, parent) {}

PlaceModel::~PlaceModel() {}

void PlaceModel::initDatas() {
	assert(_project);
	QObject::connect(_project, &fsd::Project::placesUpdated, this, &PlaceModel::updateDatas);
}

void PlaceModel::updateDatas() {
	assert(_project);
	fillDatas(_project->places());
}
} // namespace fse

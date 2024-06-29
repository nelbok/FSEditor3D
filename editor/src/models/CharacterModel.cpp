#include "CharacterModel.hpp"

#include <fsd/data/Character.hpp>
#include <fsd/data/Project.hpp>

namespace fse {

CharacterModel::CharacterModel(fsd::Project* project, QObject* parent)
	: EntityModel(project, parent) {}

CharacterModel::~CharacterModel() {}

void CharacterModel::initDatas() {
	assert(_project);
	connect(_project, &fsd::Project::charactersUpdated, this, &CharacterModel::updateDatas);
}

void CharacterModel::updateDatas() {
	assert(_project);
	fillDatas(_project->characters());
}

} // namespace fse

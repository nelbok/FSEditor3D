#include "CharacterModel.hpp"

#include <lh/data/Character.hpp>
#include <lh/data/Project.hpp>

namespace lhe {

CharacterModel::CharacterModel(lh::Project* project, QObject* parent)
	: EntityModel(project, parent) {}

CharacterModel::~CharacterModel() {}

void CharacterModel::initDatas() {
	assert(_project);
	connect(_project, &lh::Project::charactersUpdated, this, &CharacterModel::updateDatas);
}

void CharacterModel::updateDatas() {
	assert(_project);
	fillDatas(_project->characters());
}

} // namespace lhe

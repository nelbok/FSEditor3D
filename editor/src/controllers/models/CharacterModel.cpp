#include "CharacterModel.hpp"

#include <lh/data/Character.hpp>
#include <lh/data/Project.hpp>

namespace lhe {

CharacterModel::CharacterModel(QObject* parent)
	: EntityModel(parent) {}

CharacterModel::~CharacterModel() {}

void CharacterModel::init(lh::Project* project) {
	assert(project);
	connect(project, &lh::Project::charactersUpdated, this, [this, project]() {
		updateDatas(project->characters());
	});
	updateDatas(project->characters());
}

} // namespace lhe

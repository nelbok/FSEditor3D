#pragma once

#include "EntityModel.hpp"

namespace lhe {
class CharacterModel : public EntityModel {
	Q_OBJECT

public:
	CharacterModel(lh::Project* project, QObject* parent = nullptr);
	virtual ~CharacterModel();

	virtual void initDatas() override;

protected:
	virtual void updateDatas() override;
};

} // namespace lhe

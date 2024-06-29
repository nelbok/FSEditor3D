#pragma once

#include "EntityModel.hpp"

namespace fse {
class CharacterModel : public EntityModel {
	Q_OBJECT

public:
	CharacterModel(fsd::Project* project, QObject* parent = nullptr);
	virtual ~CharacterModel();

	virtual void initDatas() override;

protected:
	virtual void updateDatas() override;
};

} // namespace fse

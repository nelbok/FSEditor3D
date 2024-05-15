#pragma once

#include "EntityModel.hpp"

namespace lhe {
class CharacterModel : public EntityModel {
	Q_OBJECT

public:
	CharacterModel(QObject* parent = nullptr);
	virtual ~CharacterModel();

	virtual void init(lh::Project* project) override;
};

} // namespace lhe

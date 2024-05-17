#pragma once

#include "EntityModel.hpp"

namespace lhe {
class PlaceModel : public EntityModel {
	Q_OBJECT

public:
	PlaceModel(lh::Project* project, QObject* parent = nullptr);
	virtual ~PlaceModel();

	virtual void initDatas() override;

protected:
	virtual void updateDatas() override;
};

} // namespace lhe

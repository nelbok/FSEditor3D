#pragma once

#include "EntityModel.hpp"

namespace lhe {
class PlaceModel : public EntityModel {
	Q_OBJECT

public:
	PlaceModel(QObject* parent = nullptr);
	virtual ~PlaceModel();

	virtual void init(lh::Project* project) override;
};

} // namespace lhe

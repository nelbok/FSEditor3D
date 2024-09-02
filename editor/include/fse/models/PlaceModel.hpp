#pragma once

#include <fse/models/EntityModel.hpp>

namespace fse {
class PlaceModel : public EntityModel {
	Q_OBJECT

public:
	PlaceModel(fsd::Project* project, QObject* parent = nullptr);
	virtual ~PlaceModel();

	virtual void initDatas() override;

protected:
	virtual void updateDatas() override;
};

} // namespace fse

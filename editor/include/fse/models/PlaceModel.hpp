#pragma once

#include <fse/models/EntityModel.hpp>

namespace fse {
class PlaceModel : public EntityModel {
	Q_OBJECT

public:
	PlaceModel(fsd::Project* project, QObject* parent = nullptr);
	~PlaceModel() override;

	void initDatas() override;

protected:
	void updateDatas() override;
};

} // namespace fse

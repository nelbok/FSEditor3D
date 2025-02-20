#pragma once

#include <fse/models/EntityModel.hpp>

namespace fse {
class ObjectModel : public EntityModel {
	Q_OBJECT

public:
	ObjectModel(fsd::Project* project, QObject* parent = nullptr);
	~ObjectModel() override;

	void initDatas() override;

protected:
	void updateDatas() override;
};

} // namespace fse

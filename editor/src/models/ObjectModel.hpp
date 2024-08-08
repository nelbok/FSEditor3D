#pragma once

#include "EntityModel.hpp"

namespace fse {
class ObjectModel : public EntityModel {
	Q_OBJECT

public:
	ObjectModel(fsd::Project* project, QObject* parent = nullptr);
	virtual ~ObjectModel();

	virtual void initDatas() override;

protected:
	virtual void updateDatas() override;
};

} // namespace fse

#pragma once

#include "EntityModel.hpp"

namespace lhe {
class ModelModel : public EntityModel {
	Q_OBJECT

public:
	ModelModel(lh::Project* project, QObject* parent = nullptr);
	virtual ~ModelModel();

	virtual void initDatas() override;

protected:
	virtual void updateDatas() override;
};

} // namespace lhe

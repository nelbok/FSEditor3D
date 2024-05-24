#pragma once

#include "EntityModel.hpp"

namespace lhe {
class LinkModel : public EntityModel {
	Q_OBJECT

public:
	LinkModel(lh::Project* project, QObject* parent = nullptr);
	virtual ~LinkModel();

	virtual void initDatas() override;

protected:
	virtual void updateDatas() override;
};

} // namespace lhe

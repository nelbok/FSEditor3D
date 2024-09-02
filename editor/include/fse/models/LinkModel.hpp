#pragma once

#include <fse/models/EntityModel.hpp>

namespace fse {
class LinkModel : public EntityModel {
	Q_OBJECT

public:
	LinkModel(fsd::Project* project, QObject* parent = nullptr);
	virtual ~LinkModel();

	virtual void initDatas() override;

protected:
	virtual void updateDatas() override;
};

} // namespace fse

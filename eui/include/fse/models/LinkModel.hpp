#pragma once

#include <fse/models/EntityModel.hpp>

namespace fse {
class LinkModel : public EntityModel {
	Q_OBJECT

public:
	LinkModel(fsd::Project* project, QObject* parent = nullptr);
	~LinkModel() override;

	void initDatas() override;

protected:
	void updateDatas() override;
};

} // namespace fse

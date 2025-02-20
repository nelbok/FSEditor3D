#pragma once

#include <fse/models/EntityModel.hpp>

namespace fse {
class EntryPointModel : public EntityModel {
	Q_OBJECT

public:
	EntryPointModel(fsd::Project* project, QObject* parent = nullptr);
	~EntryPointModel() override;

	void initDatas() override;

protected:
	void updateDatas() override;
};

} // namespace fse

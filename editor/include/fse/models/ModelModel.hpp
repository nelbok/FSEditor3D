#pragma once

#include <fse/models/EntityModel.hpp>

namespace fse {
class ModelModel : public EntityModel {
	Q_OBJECT

public:
	ModelModel(fsd::Project* project, QObject* parent = nullptr);
	~ModelModel() override;

	void initDatas() override;

	QHash<int, QByteArray> roleNames() const override;

protected:
	void updateDatas() override;

	void disconnectData(fsd::Entity* entity) override;
	void connectData(fsd::Entity* entity) override;
};

} // namespace fse

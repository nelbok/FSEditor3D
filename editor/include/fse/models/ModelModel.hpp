#pragma once

#include <fse/models/EntityModel.hpp>

namespace fse {
class ModelModel : public EntityModel {
	Q_OBJECT

public:
	ModelModel(fsd::Project* project, QObject* parent = nullptr);
	virtual ~ModelModel();

	virtual void initDatas() override;

	virtual QHash<int, QByteArray> roleNames() const override;

protected:
	virtual void updateDatas() override;

	virtual void disconnectData(fsd::Entity* entity) override;
	virtual void connectData(fsd::Entity* entity) override;
};

} // namespace fse

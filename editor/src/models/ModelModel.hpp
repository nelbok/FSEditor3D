#pragma once

#include "EntityModel.hpp"

namespace lhe {
class ModelModel : public EntityModel {
	Q_OBJECT

public:
	ModelModel(lh::Project* project, QObject* parent = nullptr);
	virtual ~ModelModel();

	virtual void initDatas() override;

	virtual QHash<int, QByteArray> roleNames() const override;

protected:
	virtual void updateDatas() override;

	virtual void disconnectData(lh::Entity* entity) override;
	virtual void connectData(lh::Entity* entity) override;
};

} // namespace lhe

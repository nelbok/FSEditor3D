#pragma once

#include "EntityModel.hpp"

namespace lhe {
class LinkModel : public EntityModel {
	Q_OBJECT

public:
	LinkModel(QObject* parent = nullptr);
	virtual ~LinkModel();

	virtual void init(lh::Project* project) override;
};

} // namespace lhe

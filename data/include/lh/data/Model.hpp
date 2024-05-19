#pragma once

#include <lh/data/Entity.hpp>

namespace lh {
class Project;

class Model : public Entity {
	Q_OBJECT

public:
	Model(Project* project);
	virtual ~Model();

	virtual void reset() override;
	void copy(const Model& model);
	virtual void load(const QJsonObject& json) override;
	virtual void save(QJsonObject& json) const override;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;
};
} // namespace lh

#pragma once

#include <lh/data/Entity.hpp>

namespace lh {
class Project;

class Place : public Entity {
	Q_OBJECT

public:
	Place(Project* project);
	virtual ~Place();

	virtual void reset() override;
	void copy(const Place& place);
	virtual void load(const QJsonObject& json) override;
	virtual void save(QJsonObject& json) const override;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;
};
} // namespace lh

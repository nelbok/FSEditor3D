#pragma once

#include <fsd/data/Placement.hpp>

namespace fsd {
class Project;

class Object : public Placement {
	Q_OBJECT

public:
	Object(Project* project);
	virtual ~Object();

	virtual void reset() override;
	void copy(const Object& object);
	virtual void load(const QJsonObject& json) override;
	virtual void save(QJsonObject& json) const override;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;
};
} // namespace fsd

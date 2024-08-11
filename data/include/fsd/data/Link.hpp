#pragma once

#include <fsd/data/Placement.hpp>

namespace fsd {
class Project;

class Link : public Placement {
	Q_OBJECT
	Q_PROPERTY(Link* link READ link WRITE setLink NOTIFY linkUpdated)

public:
	Link(Project* project);
	virtual ~Link();

	virtual void reset() override;
	void copy(const Link& link);

	Link* link() const;
	void setLink(Link* link);

	virtual Type type() const override;

	virtual void load(const QJsonObject& json) override;
	virtual void save(QJsonObject& json) const override;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void linkUpdated();
};
} // namespace fsd

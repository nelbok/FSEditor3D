#pragma once

#include <lh/data/Placement.hpp>

namespace lh {
class Project;

class Link : public Placement {
	Q_OBJECT
	Q_PROPERTY(Link* link READ link WRITE setLink NOTIFY linkUpdated)

public:
	Link(Project* project);
	virtual ~Link();

	Link* link() const;
	void setLink(Link* link);

	virtual void reset() override;
	void copy(const Link& link);
	virtual void load(const QJsonObject& json) override;
	virtual void save(QJsonObject& json) const override;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void linkUpdated();
};
} // namespace lh

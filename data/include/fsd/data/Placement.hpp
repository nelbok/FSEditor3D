#pragma once

#include <fsd/data/Shape.hpp>

namespace fsd {
class Place;

class Placement : public Shape {
	Q_OBJECT
	Q_PROPERTY(Place* place READ place WRITE setPlace NOTIFY placeUpdated)

public:
	virtual void reset() override;
	void copy(const Placement& placement);

	Place* place() const;
	void setPlace(Place* place);

	virtual void load(const QJsonObject& json) override;
	virtual void save(QJsonObject& json) const override;

protected:
	Placement(Project* project, QObject* parent = nullptr);
	virtual ~Placement();

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void placeUpdated();
};
} // namespace fsd

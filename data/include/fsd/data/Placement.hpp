#pragma once

#include <QtGui/QVector3D>

#include <fsd/data/Shape.hpp>

namespace fsd {
class Place;
class Project;

class Placement : public Shape {
	Q_OBJECT
	Q_PROPERTY(QVector3D position READ position WRITE setPosition NOTIFY positionUpdated)
	Q_PROPERTY(QVector3D rotation READ rotation WRITE setRotation NOTIFY rotationUpdated)
	Q_PROPERTY(Place* place READ place WRITE setPlace NOTIFY placeUpdated)

public:
	Placement(Project* project);
	virtual ~Placement();

	virtual void reset() override;
	void copy(const Placement& placement);

	const QVector3D& position() const;
	void setPosition(const QVector3D& position);

	const QVector3D& rotation() const;
	void setRotation(const QVector3D& rotation);

	Place* place() const;
	void setPlace(Place* place);

	virtual void load(const QJsonObject& json) override;
	virtual void save(QJsonObject& json) const override;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void positionUpdated();
	void rotationUpdated();
	void placeUpdated();
};
} // namespace fsd

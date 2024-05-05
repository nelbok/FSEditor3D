#pragma once

#include <QtGui/QVector3D>

#include <lh/data/Entity.hpp>
#include <lh/data/UuidPointer.hpp>

namespace lh {
class Place;

class Placement : public Entity {
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
	QVector3D _position{};
	QVector3D _rotation{};
	UuidPointer<Place> _place{};

signals:
	void positionUpdated();
	void rotationUpdated();
	void placeUpdated();
};
} // namespace lh

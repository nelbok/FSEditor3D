#pragma once

#include <QtGui/QVector3D>

#include <fsd/data/Entity.hpp>

namespace fsd {
class Geometry : public Entity {
	Q_OBJECT
	Q_PROPERTY(QVector3D position READ position WRITE setPosition NOTIFY positionUpdated)
	Q_PROPERTY(QVector3D rotation READ rotation WRITE setRotation NOTIFY rotationUpdated)
	Q_PROPERTY(QVector3D scale READ scale WRITE setScale NOTIFY scaleUpdated)

public:
	Geometry(QObject* parent);
	virtual ~Geometry();

	virtual void reset() override;
	void copy(const Geometry& geometry);

	const QVector3D& position() const;
	void setPosition(const QVector3D& position);

	const QVector3D& rotation() const;
	void setRotation(const QVector3D& rotation);

	const QVector3D& scale() const;
	void setScale(const QVector3D& scale);

	virtual void load(const QJsonObject& json) override;
	virtual void save(QJsonObject& json) const override;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void positionUpdated();
	void rotationUpdated();
	void scaleUpdated();
};
} // namespace fsd

#pragma once

#include <QtGui/QVector3D>

#include <fsd/data/Entity.hpp>

namespace fsd {
class Geometry : public Entity {
	Q_OBJECT
	Q_PROPERTY(QVector3D localPosition READ localPosition WRITE setLocalPosition NOTIFY localPositionUpdated)
	Q_PROPERTY(QVector3D localRotation READ localRotation WRITE setLocalRotation NOTIFY localRotationUpdated)
	Q_PROPERTY(QVector3D localScale READ localScale WRITE setLocalScale NOTIFY localScaleUpdated)
	Q_PROPERTY(QVector3D globalPosition READ globalPosition NOTIFY globalPositionUpdated)
	Q_PROPERTY(QVector3D globalRotation READ globalRotation NOTIFY globalRotationUpdated)
	Q_PROPERTY(QVector3D globalScale READ globalScale NOTIFY globalScaleUpdated)

public:
	virtual void reset() override;
	void copy(const Geometry& geometry);

	const QVector3D& localPosition() const;
	void setLocalPosition(const QVector3D& localPosition);

	const QVector3D& localRotation() const;
	void setLocalRotation(const QVector3D& localRotation);

	const QVector3D& localScale() const;
	void setLocalScale(const QVector3D& localScale);

	virtual QVector3D globalPosition() const;
	virtual QVector3D globalRotation() const;
	virtual QVector3D globalScale() const;

	virtual void load(const QJsonObject& json) override;
	virtual void save(QJsonObject& json) const override;

protected:
	Geometry(Project* project, QObject* parent = nullptr);
	virtual ~Geometry();

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void localPositionUpdated();
	void localRotationUpdated();
	void localScaleUpdated();
	void globalPositionUpdated();
	void globalRotationUpdated();
	void globalScaleUpdated();
};
} // namespace fsd

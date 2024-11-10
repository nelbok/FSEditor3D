/*
 * Copyright (c) 2024 Foxxy Soft.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution
 */

#pragma once

#include <fsd/data/FSDataExport.h>

#include <QtGui/QVector3D>

#include <fsd/data/Entity.hpp>

namespace fsd {
/**
 * @brief This class adds the Y-Up location of an entity in 3D.
 *
 * Local geometry represents the entity transform in relation to its own transform.\n
 * Global geometry represents the entity transform in relation to the type of the entity.\n
 * @sa The corresponding classes that inherit Geometry for more information about global location
 */
class FSDATA_EXPORT Geometry : public Entity {
	Q_OBJECT
	/**
	 * @brief Local position of the entity in cm. Default value: 0.0.
	 */
	Q_PROPERTY(QVector3D localPosition READ localPosition WRITE setLocalPosition NOTIFY localPositionUpdated)
	/**
	 * @brief Local rotation of the entity in degree. Default value: 0.0.
	 */
	Q_PROPERTY(QVector3D localRotation READ localRotation WRITE setLocalRotation NOTIFY localRotationUpdated)
	/**
	 * @brief Local scale of the entity in ratio. Default value: 1.0.
	 */
	Q_PROPERTY(QVector3D localScale READ localScale WRITE setLocalScale NOTIFY localScaleUpdated)
	/**
	 * @brief Global position of the entity in cm.
	 */
	Q_PROPERTY(QVector3D globalPosition READ globalPosition NOTIFY globalPositionUpdated)
	/**
	 * @brief Global rotation of the entity in degree.
	 */
	Q_PROPERTY(QVector3D globalRotation READ globalRotation NOTIFY globalRotationUpdated)
	/**
	 * @brief Global scale of the entity in ratio.
	 */
	Q_PROPERTY(QVector3D globalScale READ globalScale NOTIFY globalScaleUpdated)

public:
	void reset() override;
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

	void load(const QJsonObject& json) override;
	void save(QJsonObject& json) const override;

protected:
	Geometry(Project* project, QObject* parent = nullptr);
	~Geometry() override;

	using Entity::copy;

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

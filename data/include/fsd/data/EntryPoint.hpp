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
class Place;

/**
 * @brief An entry point to your project.
 */
class FSDATA_EXPORT EntryPoint final : public Entity {
	Q_OBJECT
	/**
	 * @brief Position on Y-Up in cm.
	 */
	Q_PROPERTY(QVector3D position READ position WRITE setPosition NOTIFY positionUpdated)
	/**
	 * @brief Rotation on Y-axis in degree.
	 */
	Q_PROPERTY(float rotation READ rotation WRITE setRotation NOTIFY rotationUpdated)
	/**
	 * @brief The connected place.
	 */
	Q_PROPERTY(Place* place READ place WRITE setPlace NOTIFY placeUpdated)

public:
	explicit EntryPoint(Project* project);
	~EntryPoint() override;

	void reset() override;
	void copy(const EntryPoint& entryPoint);

	const QVector3D& position() const;
	void setPosition(const QVector3D& position);

	float rotation() const;
	void setRotation(float rotation);

	Place* place() const;
	void setPlace(Place* place);

	Type type() const override;

	void load(const QJsonObject& json) override;
	void save(QJsonObject& json) const override;

private:
	using Entity::copy;

	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void positionUpdated();
	void rotationUpdated();
	void placeUpdated();
};
} // namespace fsd

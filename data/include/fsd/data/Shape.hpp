/*
 * Copyright (c) 2024 Foxxy Soft.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution
 */

#pragma once

#include <fsd/data/Geometry.hpp>

namespace fsd {
class Model;

/**
 * @brief This class adds a connection to a Model.
 */
class Shape : public Geometry {
	Q_OBJECT
	/**
	 * @brief The connected model to this entity.
	 *
	 * Global geometry represents the entity transform in relation to the model transform.\n
	 */
	Q_PROPERTY(Model* model READ model WRITE setModel NOTIFY modelUpdated)

public:
	void reset() override;
	void copy(const Shape& shape);

	Model* model() const;
	void setModel(Model* model);

	QVector3D globalPosition() const override;
	QVector3D globalRotation() const override;
	QVector3D globalScale() const override;

	void load(const QJsonObject& json) override;
	void save(QJsonObject& json) const override;

protected:
	Shape(Project* project, QObject* parent = nullptr);
	~Shape() override;

	using Geometry::copy;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void modelUpdated();
};
} // namespace fsd

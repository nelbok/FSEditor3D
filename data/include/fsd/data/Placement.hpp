/*
 * Copyright (c) 2024 Foxxy Soft.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution
 */

#pragma once

#include <fsd/data/Shape.hpp>

namespace fsd {
class Place;

/**
 * @brief This class add a connection to a place.
 */
class Placement : public Shape {
	Q_OBJECT
	/**
	 * @brief The connected place to this entity.
	 */
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

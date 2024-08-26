/*
 * Copyright (c) 2024 Foxxy Soft.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution
 */

#pragma once

#include <fsd/data/Placement.hpp>

namespace fsd {
/**
 * @brief An basic object in a Place.
 */
class Object final : public Placement {
	Q_OBJECT

public:
	Object(Project* project);
	virtual ~Object();

	virtual void reset() override;
	void copy(const Object& object);

	virtual Type type() const override;

	virtual void load(const QJsonObject& json) override;
	virtual void save(QJsonObject& json) const override;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;
};
} // namespace fsd

/*
 * Copyright (c) 2024 Foxxy Soft.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution
 */

#pragma once

#include <fsd/data/Shape.hpp>

namespace fsd {
/**
 * @brief Place that contains Links and/or Objects.
 */
class Place final : public Shape {
	Q_OBJECT

public:
	explicit Place(Project* project);
	~Place() override;

	void reset() override;
	void copy(const Place& place);

	Type type() const override;

	void load(const QJsonObject& json) override;
	void save(QJsonObject& json) const override;

private:
	using Shape::copy;

	struct Impl;
	std::unique_ptr<Impl> _impl;
};
} // namespace fsd

/*
 * Copyright (c) 2024 Foxxy Soft.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution
 */

#pragma once

#include <fsd/data/FSDataExport.h>

#include <fsd/data/Placement.hpp>

namespace fsd {
/**
 * @brief An basic object in a Place.
 */
class FSDATA_EXPORT Object final : public Placement {
	Q_OBJECT

public:
	explicit Object(Project* project);
	~Object() override;

	void reset() override;
	void copy(const Object& object);

	Type type() const override;

	void load(const QJsonObject& json) override;
	void save(QJsonObject& json) const override;

private:
	using Placement::copy;

	struct Impl;
	std::unique_ptr<Impl> _impl;
};
} // namespace fsd

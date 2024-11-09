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
 * @brief An entity to link two places together.
 *
 * By setting link property, you can indicate that a place is linked to another place.\n
 * The link is only one-way, if you want a two-way, you need to link the other link to this one.
 */
class Link final : public Placement {
	Q_OBJECT
	/**
	 * @brief The connected link to this one.
	 */
	Q_PROPERTY(Link* link READ link WRITE setLink NOTIFY linkUpdated)

public:
	explicit Link(Project* project);
	~Link() override;

	void reset() override;
	void copy(const Link& link);

	Link* link() const;
	void setLink(Link* link);

	Type type() const override;

	void load(const QJsonObject& json) override;
	void save(QJsonObject& json) const override;

private:
	using Placement::copy;

	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void linkUpdated();
};
} // namespace fsd

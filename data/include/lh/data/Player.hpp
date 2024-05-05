#pragma once

#include "Character.hpp"

namespace lh {

class Player : public Character {
	Q_OBJECT

public:
	Player(Project* project);
	virtual ~Player();

	virtual void reset() override;
	void copy(const Player& player);
	virtual void load(const QJsonObject& json) override;
	virtual void save(QJsonObject& json) const override;
};
} // namespace lh

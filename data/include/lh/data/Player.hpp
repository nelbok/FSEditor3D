#pragma once

#include "Character.hpp"

namespace lh {

class Player : public Character {
	Q_OBJECT

public:
	Player(Project* project);
	virtual ~Player();

	void init();
};
} // namespace lh

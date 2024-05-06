#include <lh/data/Player.hpp>

namespace lh {
struct Player::Impl {};

Player::Player(Project* project)
	: Character(project)
	, _impl{ std::make_unique<Impl>() } {}

Player::~Player() {}

void Player::reset() {
	Character::reset();
}

void Player::copy(const Player& player) {
	Character::copy(player);
}

void Player::load(const QJsonObject& json) {
	Character::load(json);
}

void Player::save(QJsonObject& json) const {
	Character::save(json);
}
} // namespace lh

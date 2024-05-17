#include "CharacterCommand.hpp"

#include "../Commands.hpp"
#include "ValueCommand.hpp"

namespace lhe {

CharacterCommand::CharacterCommand(Commands* commands)
	: QObject(commands)
	, _c{ commands } {
	assert(commands);
}

CharacterCommand::~CharacterCommand() {}

void CharacterCommand::setHair(lh::Character* c, const QColor& newValue) {
	addValueCommand(_c, c, &lh::Character::setHair, &lh::Character::hair, newValue);
}

void CharacterCommand::setSkin(lh::Character* c, const QColor& newValue) {
	addValueCommand(_c, c, &lh::Character::setSkin, &lh::Character::skin, newValue);
}

void CharacterCommand::setClothes(lh::Character* c, const QColor& newValue) {
	addValueCommand(_c, c, &lh::Character::setClothes, &lh::Character::clothes, newValue);
}

void CharacterCommand::setHeight(lh::Character* c, quint8 newValue) {
	addValueCommand(_c, c, &lh::Character::setHeight, &lh::Character::height, newValue);
}

void CharacterCommand::setSpecies(lh::Character* c, lh::Character::Species newValue) {
	addValueCommand(_c, c, &lh::Character::setSpecies, &lh::Character::species, newValue);
}

void CharacterCommand::setGender(lh::Character* c, lh::Character::Gender newValue) {
	addValueCommand(_c, c, &lh::Character::setGender, &lh::Character::gender, newValue);
}

} // namespace lhe

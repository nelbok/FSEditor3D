#include "CharacterCommand.hpp"

#include "Commands.hpp"
#include "ValueCommand.hpp"

namespace fse {

CharacterCommand::CharacterCommand(Commands* commands)
	: QObject(commands)
	, _c{ commands } {
	assert(commands);
}

CharacterCommand::~CharacterCommand() {}

void CharacterCommand::setHair(fsd::Character* c, const QColor& newValue) {
	addValueCommand(_c, c, &fsd::Character::setHair, &fsd::Character::hair, newValue);
}

void CharacterCommand::setSkin(fsd::Character* c, const QColor& newValue) {
	addValueCommand(_c, c, &fsd::Character::setSkin, &fsd::Character::skin, newValue);
}

void CharacterCommand::setClothes(fsd::Character* c, const QColor& newValue) {
	addValueCommand(_c, c, &fsd::Character::setClothes, &fsd::Character::clothes, newValue);
}

void CharacterCommand::setHeight(fsd::Character* c, quint8 newValue) {
	addValueCommand(_c, c, &fsd::Character::setHeight, &fsd::Character::height, newValue);
}

void CharacterCommand::setSpecies(fsd::Character* c, fsd::Character::Species newValue) {
	addValueCommand(_c, c, &fsd::Character::setSpecies, &fsd::Character::species, newValue);
}

void CharacterCommand::setGender(fsd::Character* c, fsd::Character::Gender newValue) {
	addValueCommand(_c, c, &fsd::Character::setGender, &fsd::Character::gender, newValue);
}

} // namespace fse

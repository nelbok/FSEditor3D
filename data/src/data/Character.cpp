#include <lh/data/Character.hpp>

#include <lh/io/Json.hpp>

#include "common/Tools.hpp"

namespace lh {
struct Character::Impl {
	QColor hair{};
	QColor skin{};
	QColor clothes{};
	quint8 height{};
	Species species{};
	Gender gender{};
};

Character::Character(Project* project)
	: Placement(project)
	, _impl{ std::make_unique<Impl>() } {}

Character::~Character() {}

void Character::reset() {
	Placement::reset();
	setHair("brown");
	setSkin("mistyrose");
	setClothes("red");
	setHeight(170);
	setSpecies(Species::Human);
	setGender(Gender::Male);
}

void Character::copy(const Character& character) {
	Placement::copy(character);
	setHair(character.hair());
	setSkin(character.skin());
	setClothes(character.clothes());
	setHeight(character.height());
	setSpecies(character.species());
	setGender(character.gender());
}

const QColor& Character::hair() const {
	return _impl->hair;
}

void Character::setHair(const QColor& hair) {
	TOOLS_SETTER(Character, hair);
}

const QColor& Character::skin() const {
	return _impl->skin;
}

void Character::setSkin(const QColor& skin) {
	TOOLS_SETTER(Character, skin);
}

const QColor& Character::clothes() const {
	return _impl->clothes;
}

void Character::setClothes(const QColor& clothes) {
	TOOLS_SETTER(Character, clothes);
}

quint8 Character::height() const {
	return _impl->height;
}

void Character::setHeight(quint8 height) {
	TOOLS_SETTER(Character, height);
}

Character::Species Character::species() const {
	return _impl->species;
}

void Character::setSpecies(Species species) {
	TOOLS_SETTER(Character, species);
}

Character::Gender Character::gender() const {
	return _impl->gender;
}

void Character::setGender(Gender gender) {
	TOOLS_SETTER(Character, gender);
}

void Character::load(const QJsonObject& json) {
	Entity::load(json);
	setHair(Json::toColor(Json::toObject("hair", json)));
	setSkin(Json::toColor(Json::toObject("skin", json)));
	setClothes(Json::toColor(Json::toObject("clothes", json)));
	setHeight(Json::toInt("height", json));
	setSpecies(static_cast<Character::Species>(Json::toInt("species", json)));
	setGender(static_cast<Character::Gender>(Json::toInt("gender", json)));
}

void Character::save(QJsonObject& json) const {
	Entity::save(json);
	json["clothes"] = Json::fromColor(_impl->clothes);
	json["hair"] = Json::fromColor(_impl->hair);
	json["skin"] = Json::fromColor(_impl->skin);
	json["height"] = _impl->height;
	json["species"] = static_cast<int>(_impl->species);
	json["gender"] = static_cast<int>(_impl->gender);
}
} // namespace lh

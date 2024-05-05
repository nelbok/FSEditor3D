#include <lh/data/Character.hpp>

#include <lh/io/Json.hpp>

namespace lh {
Character::Character(Project* project)
	: Placement(project) {
	Character::reset();
}

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
	return _hair;
}

void Character::setHair(const QColor& hair) {
	if (_hair != hair) {
		_hair = hair;
		emit hairUpdated();
	}
}

const QColor& Character::skin() const {
	return _skin;
}

void Character::setSkin(const QColor& skin) {
	if (_skin != skin) {
		_skin = skin;
		emit skinUpdated();
	}
}

const QColor& Character::clothes() const {
	return _clothes;
}

void Character::setClothes(const QColor& clothes) {
	if (_clothes != clothes) {
		_clothes = clothes;
		emit clothesUpdated();
	}
}

quint8 Character::height() const {
	return _height;
}

void Character::setHeight(quint8 height) {
	if (_height != height) {
		_height = height;
		emit heightUpdated();
	}
}

Character::Species Character::species() const {
	return _species;
}

void Character::setSpecies(Species species) {
	if (_species != species) {
		_species = species;
		emit speciesUpdated();
	}
}

Character::Gender Character::gender() const {
	return _gender;
}

void Character::setGender(Gender gender) {
	if (_gender != gender) {
		_gender = gender;
		emit genderUpdated();
	}
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
	json["clothes"] = Json::fromColor(_clothes);
	json["hair"] = Json::fromColor(_hair);
	json["skin"] = Json::fromColor(_skin);
	json["height"] = _height;
	json["species"] = static_cast<int>(_species);
	json["gender"] = static_cast<int>(_gender);
}
} // namespace lh

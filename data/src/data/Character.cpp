#include <lh/data/Character.hpp>
#include <lh/io/Json.hpp>

namespace lh {
Character::Character(Project* project)
	: Entity(project) {}

Character::~Character() {}

void Character::setPosition(const QVector3D& position) {
	if (_position != position) {
		_position = position;
		emit positionUpdated();
	}
}

void Character::setCamera(const QVector2D& camera) {
	if (_camera != camera) {
		_camera = camera;
		emit cameraUpdated();
	}
}

void Character::setHair(const QColor& hair) {
	if (_hair != hair) {
		_hair = hair;
		emit hairUpdated();
	}
}

void Character::setSkin(const QColor& skin) {
	if (_skin != skin) {
		_skin = skin;
		emit skinUpdated();
	}
}

void Character::setClothes(const QColor& clothes) {
	if (_clothes != clothes) {
		_clothes = clothes;
		emit clothesUpdated();
	}
}

void Character::setHeight(quint8 height) {
	if (_height != height) {
		_height = height;
		emit heightUpdated();
	}
}

void Character::setSpecies(Species species) {
	if (_species != species) {
		_species = species;
		emit speciesUpdated();
	}
}

void Character::setGender(Gender gender) {
	if (_gender != gender) {
		_gender = gender;
		emit genderUpdated();
	}
}

void Character::load(const QJsonObject& json) {
	Entity::load(json);
	setPosition(Json::toVector3D(Json::toObject("position", json)));
	setCamera(Json::toVector2D(Json::toObject("camera", json)));
	setHair(Json::toColor(Json::toObject("hair", json)));
	setSkin(Json::toColor(Json::toObject("skin", json)));
	setClothes(Json::toColor(Json::toObject("clothes", json)));
	setHeight(Json::toInt("height", json));
	setSpecies(static_cast<Character::Species>(Json::toInt("species", json)));
	setGender(static_cast<Character::Gender>(Json::toInt("gender", json)));
}

void Character::save(QJsonObject& json) const {
	Entity::save(json);
	json["position"] = Json::fromVector3D(_position);
	json["camera"] = Json::fromVector2D(_camera);
	json["clothes"] = Json::fromColor(_clothes);
	json["hair"] = Json::fromColor(_hair);
	json["skin"] = Json::fromColor(_skin);
	json["height"] = _height;
	json["species"] = static_cast<int>(_species);
	json["gender"] = static_cast<int>(_gender);
}
} // namespace lh

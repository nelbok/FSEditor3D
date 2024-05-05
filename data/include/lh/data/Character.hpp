#pragma once

#include <QtGui/QColor>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>

#include <lh/data/Entity.hpp>

namespace lh {

class Character : public Entity {
	Q_OBJECT
	Q_PROPERTY(QVector3D position READ position WRITE setPosition NOTIFY positionUpdated)
	Q_PROPERTY(QVector2D camera READ camera WRITE setCamera NOTIFY cameraUpdated)
	Q_PROPERTY(QColor hair READ hair WRITE setHair NOTIFY hairUpdated)
	Q_PROPERTY(QColor skin READ skin WRITE setSkin NOTIFY skinUpdated)
	Q_PROPERTY(QColor clothes READ clothes WRITE setClothes NOTIFY clothesUpdated)
	Q_PROPERTY(quint8 height READ height WRITE setHeight NOTIFY heightUpdated)
	Q_PROPERTY(Species species READ species WRITE setSpecies NOTIFY speciesUpdated)
	Q_PROPERTY(Gender gender READ gender WRITE setGender NOTIFY genderUpdated)

public:
	enum class Species {
		Human,

		// Demi human
		Fox,
		Cat,
		Dog,
		Bun,
		Rat,

		// Monster
		Goblin,
		Ogre,
		Orc,
		Troll,
		Lizard,
	};
	Q_ENUM(Species)
	enum class Gender { Male, Female };
	Q_ENUM(Gender)

	Character(Project* project);
	virtual ~Character();

	// clang-format off
	// Position is in centimeters not meters like Eno
	const QVector3D& position() const { return _position; }
	void setPosition(const QVector3D& position);

	const QVector2D& camera() const { return _camera; }
	void setCamera(const QVector2D& camera);

	const QColor& hair() const { return _hair; }
	void setHair(const QColor& hair);

	const QColor& skin() const { return _skin; }
	void setSkin(const QColor& skin);

	const QColor& clothes() const { return _clothes; }
	void setClothes(const QColor& clothes);

	// Height is in centimeters not meters like Eno
	quint8 height() const { return _height; }
	void setHeight(quint8 height);

	Species species() const { return _species; }
	void setSpecies(Species species);

	Gender gender() const { return _gender; }
	void setGender(Gender gender);
	// clang-format on

	virtual void load(const QJsonObject& json) override;
	virtual void save(QJsonObject& json) const override;

private:
	QVector3D _position{ 0, 0, 0 };
	QVector2D _camera{ 0, 0 };
	QColor _hair{};
	QColor _skin{};
	QColor _clothes{};
	quint8 _height{ 170 };
	Species _species{ Species::Human };
	Gender _gender{ Gender::Male };

signals:
	void positionUpdated();
	void cameraUpdated();
	void hairUpdated();
	void skinUpdated();
	void clothesUpdated();
	void heightUpdated();
	void speciesUpdated();
	void genderUpdated();
};
} // namespace lh

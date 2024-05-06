#pragma once

#include <QtGui/QColor>

#include <lh/data/Placement.hpp>

namespace lh {

class Character : public Placement {
	Q_OBJECT
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

	virtual void reset() override;
	void copy(const Character& character);

	const QColor& hair() const;
	void setHair(const QColor& hair);

	const QColor& skin() const;
	void setSkin(const QColor& skin);

	const QColor& clothes() const;
	void setClothes(const QColor& clothes);

	quint8 height() const;
	void setHeight(quint8 height);

	Species species() const;
	void setSpecies(Species species);

	Gender gender() const;
	void setGender(Gender gender);

	virtual void load(const QJsonObject& json) override;
	virtual void save(QJsonObject& json) const override;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void hairUpdated();
	void skinUpdated();
	void clothesUpdated();
	void heightUpdated();
	void speciesUpdated();
	void genderUpdated();
};
} // namespace lh

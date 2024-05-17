#pragma once

#include <QtCore/QObject>

#include <lh/data/Character.hpp>

namespace lhe {
class Commands;

class CharacterCommand : public QObject {
	Q_OBJECT

public:
	CharacterCommand(Commands* commands);
	virtual ~CharacterCommand();

	Q_INVOKABLE void setHair(lh::Character* character, const QColor& hair);
	Q_INVOKABLE void setSkin(lh::Character* character, const QColor& skin);
	Q_INVOKABLE void setClothes(lh::Character* character, const QColor& clothes);
	Q_INVOKABLE void setHeight(lh::Character* character, quint8 height);
	Q_INVOKABLE void setSpecies(lh::Character* character, lh::Character::Species species);
	Q_INVOKABLE void setGender(lh::Character* character, lh::Character::Gender gender);

protected:
	Commands* _c{ nullptr };
};
} // namespace lhe

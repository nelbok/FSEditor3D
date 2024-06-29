#pragma once

#include <QtCore/QObject>

#include <fsd/data/Character.hpp>

namespace fse {
class Commands;

class CharacterCommand : public QObject {
	Q_OBJECT

public:
	CharacterCommand(Commands* commands);
	virtual ~CharacterCommand();

	Q_INVOKABLE void setHair(fsd::Character* character, const QColor& hair);
	Q_INVOKABLE void setSkin(fsd::Character* character, const QColor& skin);
	Q_INVOKABLE void setClothes(fsd::Character* character, const QColor& clothes);
	Q_INVOKABLE void setHeight(fsd::Character* character, quint8 height);
	Q_INVOKABLE void setSpecies(fsd::Character* character, fsd::Character::Species species);
	Q_INVOKABLE void setGender(fsd::Character* character, fsd::Character::Gender gender);

protected:
	Commands* _c{ nullptr };
};
} // namespace fse

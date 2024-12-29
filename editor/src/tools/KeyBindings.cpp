#include <fse/tools/KeyBindings.hpp>

namespace fse {
KeyBindings::KeyBindings(QObject* parent)
	: QObject(parent) {}

KeyBindings::~KeyBindings() = default;

KeyBindings& KeyBindings::operator=(const KeyBindings& other) {
	this->forward1 = other.forward1;
	this->forward2 = other.forward2;
	this->backward1 = other.backward1;
	this->backward2 = other.backward2;
	this->left1 = other.left1;
	this->left2 = other.left2;
	this->right1 = other.right1;
	this->right2 = other.right2;
	this->up1 = other.up1;
	this->up2 = other.up2;
	this->down1 = other.down1;
	this->down2 = other.down2;
	this->sprint = other.sprint;

	emit updated();

	return *this;
}

bool KeyBindings::operator==(const KeyBindings& other) const {
	bool ret = true;

	ret &= this->forward1 == other.forward1;
	ret &= this->forward2 == other.forward2;
	ret &= this->backward1 == other.backward1;
	ret &= this->backward2 == other.backward2;
	ret &= this->left1 == other.left1;
	ret &= this->left2 == other.left2;
	ret &= this->right1 == other.right1;
	ret &= this->right2 == other.right2;
	ret &= this->up1 == other.up1;
	ret &= this->up2 == other.up2;
	ret &= this->down1 == other.down1;
	ret &= this->down2 == other.down2;
	ret &= this->sprint == other.sprint;

	return ret;
}
} // namespace fse

#include <fse/managers/KeyBindingsManager.hpp>

#include <QtGui/QKeySequence>

namespace fse {

struct KeyBindingsManager::Impl {
	KeyBindingsType current{ KeyBindingsType::Custom };
	KeyBindings* keyBindings{ nullptr };
	KeyBindings* qwertyBindings{ nullptr };
	KeyBindings* azertyBindings{ nullptr };

	void loadQwertyBindings() {
		assert(qwertyBindings);
		qwertyBindings->forward1 = Qt::Key_W;
		qwertyBindings->forward2 = Qt::Key_Up;
		qwertyBindings->backward1 = Qt::Key_S;
		qwertyBindings->backward2 = Qt::Key_Down;
		qwertyBindings->left1 = Qt::Key_A;
		qwertyBindings->left2 = Qt::Key_Left;
		qwertyBindings->right1 = Qt::Key_D;
		qwertyBindings->right2 = Qt::Key_Right;
		qwertyBindings->up1 = Qt::Key_R;
		qwertyBindings->up2 = Qt::Key_PageUp;
		qwertyBindings->down1 = Qt::Key_F;
		qwertyBindings->down2 = Qt::Key_PageDown;
		qwertyBindings->sprint = Qt::Key_Shift;
	}

	void loadAzertyBindings() {
		assert(azertyBindings);
		azertyBindings->forward1 = Qt::Key_Z;
		azertyBindings->forward2 = Qt::Key_Up;
		azertyBindings->backward1 = Qt::Key_S;
		azertyBindings->backward2 = Qt::Key_Down;
		azertyBindings->left1 = Qt::Key_Q;
		azertyBindings->left2 = Qt::Key_Left;
		azertyBindings->right1 = Qt::Key_D;
		azertyBindings->right2 = Qt::Key_Right;
		azertyBindings->up1 = Qt::Key_R;
		azertyBindings->up2 = Qt::Key_PageUp;
		azertyBindings->down1 = Qt::Key_F;
		azertyBindings->down2 = Qt::Key_PageDown;
		azertyBindings->sprint = Qt::Key_Shift;
	}
};

KeyBindingsManager::KeyBindingsManager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

KeyBindingsManager::~KeyBindingsManager() = default;

void KeyBindingsManager::init() {
	_impl->keyBindings = new KeyBindings(this);
	_impl->qwertyBindings = new KeyBindings(this);
	_impl->azertyBindings = new KeyBindings(this);

	_impl->loadQwertyBindings();
	_impl->loadAzertyBindings();

	connect(_impl->keyBindings, &KeyBindings::updated, this, &KeyBindingsManager::updateCurrent);
}

KeyBindingsManager::KeyBindingsType KeyBindingsManager::current() const {
	return _impl->current;
}

void KeyBindingsManager::setCurrent(KeyBindingsType current) {
	if (_impl->current != current) {
		_impl->current = current;

		switch (_impl->current) {
			case KeyBindingsType::Qwerty:
				_impl->keyBindings->operator=(*_impl->qwertyBindings);
				break;
			case KeyBindingsType::Azerty:
				_impl->keyBindings->operator=(*_impl->azertyBindings);
				break;
			default:
				break;
		}

		emit currentUpdated();
	}
}

KeyBindings* KeyBindingsManager::keyBindings() const {
	return _impl->keyBindings;
}

QString KeyBindingsManager::toString(Qt::Key key) const {
	return QKeySequence(key).toString();
}

void KeyBindingsManager::updateCurrent() {
	if (_impl->keyBindings->operator==(*_impl->qwertyBindings)) {
		setCurrent(KeyBindingsType::Qwerty);
	} else if (_impl->keyBindings->operator==(*_impl->azertyBindings)) {
		setCurrent(KeyBindingsType::Azerty);
	} else {
		setCurrent(KeyBindingsType::Custom);
	}
}
} // namespace fse

#include <fse/managers/KeyBindingsManager.hpp>

#include <QtGui/QKeySequence>

namespace fse {

struct KeyBindingsManager::Impl {
	KeyBindingsType current{ KeyBindingsType::Qwerty };
	KeyBindings* keyBindings{ nullptr };
};

KeyBindingsManager::KeyBindingsManager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

KeyBindingsManager::~KeyBindingsManager() = default;

void KeyBindingsManager::init() {
	_impl->keyBindings = new KeyBindings(this);
}

KeyBindingsManager::KeyBindingsType KeyBindingsManager::current() const {
	return _impl->current;
}

void KeyBindingsManager::setCurrent(KeyBindingsType current) {
	if (_impl->current != current) {
		_impl->current = current;
		emit currentUpdated();
	}
}

KeyBindings* KeyBindingsManager::keyBindings() const {
	return _impl->keyBindings;
}

QString KeyBindingsManager::toString(Qt::Key key) const {
	return QKeySequence(key).toString();
}
} // namespace fse

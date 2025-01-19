#include <fse/managers/TranslationsManager.hpp>

#include <QtCore/QCoreApplication>
#include <QtCore/QLocale>
#include <QtCore/QTranslator>

#include <fse/managers/ErrorsManager.hpp>

#include "tools/DefaultSettings.hpp"

namespace fse {

struct TranslationsManager::Impl {
	QTranslator translator;
	QString current{ DefaultSettings::uiTranslationValue };
	ErrorsManager* manager{ nullptr };

	void installTranslator() {
		if (translator.load(QLocale(current), "app", "_", ":/translations")) {
			QCoreApplication::installTranslator(&translator);
		} else {
			assert(!"Translation not found");
			manager->setType(ErrorsManager::Type::TranslatorError);
		}
	}
};

TranslationsManager::TranslationsManager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

TranslationsManager::~TranslationsManager() = default;

void TranslationsManager::init(ErrorsManager* manager) {
	assert(!_impl->manager);
	_impl->manager = manager;
	_impl->installTranslator();
}

QString TranslationsManager::current() const {
	return _impl->current;
}

void TranslationsManager::setCurrent(const QString& current) {
	if (_impl->current != current) {
		_impl->current = current;
		_impl->installTranslator();
		emit currentUpdated();
	}
}
} // namespace fse

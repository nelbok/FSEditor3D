#pragma once

#include <QtTest/QtTest>

#include <fse/managers/ErrorsManager.hpp>
#include <fse/managers/TranslationsManager.hpp>
#include <fse/Manager.hpp>

struct TestTranslations {
	void run() {
		fse::Manager manager;
		manager.init();
		QCOMPARE(manager.errorsManager()->type(), fse::ErrorsManager::Type::NoError);

		// English
		manager.translationsManager()->setCurrent("en");
		QCOMPARE(manager.translationsManager()->current(), "en");
		QCOMPARE(QCoreApplication::translate("EntityModel", "None"), "None");

		// French
		manager.translationsManager()->setCurrent("fr");
		QCOMPARE(manager.translationsManager()->current(), "fr");
		QCOMPARE(QCoreApplication::translate("EntityModel", "None"), "Aucun(e)");
	}
};

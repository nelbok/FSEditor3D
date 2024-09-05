#pragma once

#include <QtTest/QtTest>

#include <fse/managers/ErrorsManager.hpp>
#include <fse/managers/StylesManager.hpp>
#include <fse/Manager.hpp>

struct TestStyles {
	void run() {
		fse::Manager manager;
		manager.init();
		QCOMPARE(manager.errorsManager()->type(), fse::ErrorsManager::Type::NoError);
		QCOMPARE(manager.stylesManager()->current(), "basic");

		const auto& style = manager.stylesManager()->style();
		QVERIFY(style.newFile != "");
		QVERIFY(style.loadFile != "");
		QVERIFY(style.saveFile != "");
		QVERIFY(style.undo != "");
		QVERIFY(style.redo != "");
		QVERIFY(style.settings != "");
	}
};

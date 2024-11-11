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
		QVERIFY(style.icons.newFile != "");
		QVERIFY(style.icons.loadFile != "");
		QVERIFY(style.icons.saveFile != "");
		QVERIFY(style.icons.undo != "");
		QVERIFY(style.icons.redo != "");
		QVERIFY(style.icons.settings != "");
	}
};

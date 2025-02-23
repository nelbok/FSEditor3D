#pragma once

#include <QtTest/QtTest>

#include <fsd/data/Model.hpp>

#include <fse/managers/FileManager.hpp>
#include <fse/managers/InterfaceManager.hpp>
#include <fse/Manager.hpp>

#include "Dummy.hpp"

struct TestBalsam {
	void run() {
		const QString dirPath = QCoreApplication::applicationDirPath();
		const QString saveDir = dirPath + "/testsave";
		const QString savePath = saveDir + "/test.json";
		const QString mtlPath = dirPath + "/test.mtl";
		const QString objPath = dirPath + "/test.obj";

		QVERIFY(QFileInfo::exists(mtlPath));
		QVERIFY(QFileInfo::exists(objPath));

		fse::Manager manager;
		manager.init();
		fse::Balsam* balsam = manager.balsam();
		fse::InterfaceManager* interface = manager.interfaceManager();

		fsd::Project* project = manager.project();
		Dummy::build(*project);

		// Dummy save
		QDir().mkpath(saveDir);
		QObject::connect(interface, &fse::InterfaceManager::openSaveDialog, interface, [interface, savePath]() {
			interface->saveFile(QUrl::fromLocalFile(savePath));
		});
		interface->save();
		while (!interface->isInterfaceEnabled()) {
			QThread::msleep(100);
			QCoreApplication::processEvents();
		}
		QCOMPARE(manager.fileManager()->result(), fsd::FileManager::Result::Success);
		QCOMPARE(manager.fileManager()->path(), QUrl::fromLocalFile(savePath));

		fsd::Model* model = project->models()->at(0);

		qWarning(balsam->balsamPath().toLocalFile().toStdString().c_str());

		balsam->generate(model, QUrl::fromLocalFile(dirPath + "/test.obj"), { "-platform", QGuiApplication::platformName() });
		while (balsam->state() != QProcess::NotRunning) {
			QThread::msleep(100);
			QCoreApplication::processEvents();
		}
		QCOMPARE(balsam->error(), QProcess::UnknownError);

		QCOMPARE(model->qmlName(), "Test.qml");
		QVERIFY(QFileInfo::exists(balsam->qmlPath(model).toLocalFile()));
	}
};

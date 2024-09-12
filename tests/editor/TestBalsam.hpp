#pragma once

#include <QtTest/QtTest>

#include <fsd/data/Model.hpp>

#include <fse/managers/FileManager.hpp>
#include <fse/Manager.hpp>

#include "Dummy.hpp"

struct TestBalsam {
	void run() {
		const QString dirPath = qApp->applicationDirPath();
		const QString saveDir = dirPath + "/testsave";
		const QString savePath = saveDir + "/test.json";
		const QString mtlPath = dirPath + "/test.mtl";
		const QString objPath = dirPath + "/test.obj";

		QVERIFY(QFileInfo::exists(mtlPath));
		QVERIFY(QFileInfo::exists(objPath));

		fse::Manager manager;
		manager.init();
		fse::Balsam* balsam = manager.balsam();

		fsd::Project* project = manager.project();
		Dummy::build(*project);

		// Dummy save
		QDir().mkpath(saveDir);
		manager.fileManager()->save(QUrl::fromLocalFile(savePath));
		while (manager.fileManager()->status() != fse::FileManager::Status::Stopped) {
			QThread::msleep(100);
			qApp->processEvents();
		}
		QCOMPARE(manager.fileManager()->result(), fsd::FileManager::Result::Success);
		QCOMPARE(manager.fileManager()->path(), QUrl::fromLocalFile(savePath));

		fsd::Model* model = project->models().at(0);

		balsam->generate(model, QUrl::fromLocalFile(dirPath + "/test.obj"), { "-platform", qApp->platformName() });
		while (balsam->state() != QProcess::NotRunning) {
			QThread::msleep(100);
			qApp->processEvents();
		}
		QCOMPARE(balsam->error(), QProcess::UnknownError);

		QCOMPARE(model->qmlName(), "Test.qml");
		QVERIFY(QFileInfo::exists(balsam->qmlPath(model).toLocalFile()));
	}
};

#pragma once

#include <QtCore/QCoreApplication>
#include <QtTest/QtTest>

#include <fsd/data/Model.hpp>

#include <fse/Manager.hpp>

#include "Dummy.hpp"

struct TestBalsam {
	void run() {
		const QString& dirPath = qApp->applicationDirPath();
		const QString mtlPath = dirPath + "/test.mtl";
		const QString objPath = dirPath + "/test.obj";

		QVERIFY(QFileInfo::exists(mtlPath));
		QVERIFY(QFileInfo::exists(objPath));

		fse::Manager manager;
		manager.init();
		fse::Balsam* balsam = manager.balsam();

		fsd::Project* project = manager.project();
		Dummy::build(*project);

		fsd::Model* model = project->models().at(0);

		balsam->generate(model, QUrl::fromLocalFile(dirPath + "/test.obj"));

		while (balsam->state() != QProcess::NotRunning) {
			QThread::sleep(1);
			qApp->processEvents();
		}

		QCOMPARE(model->qmlName(), "Test.qml");
		QVERIFY(QFileInfo::exists(balsam->qmlPath(model).toLocalFile()));
	}
};

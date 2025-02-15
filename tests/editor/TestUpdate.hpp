#pragma once

#include <QtCore/QCoreApplication>
#include <QtTest/QtTest>

#include <fse/managers/UpdateManager.hpp>
#include <fse/Manager.hpp>

struct TestUpdate {
	void run() {
		fse::Manager manager;
		manager.init();
		auto* update = manager.updateManager();

		// Init the test
		QCoreApplication::setApplicationVersion("0.0.0");
		QSignalSpy spy(update, &fse::UpdateManager::newVersionAvailable);

		// Trigger the test
		update->checkForUpdates();

		// Waiting...
		int count = 0;
		while (update->status() == fse::UpdateManager::Status::Processing) {
			QThread::msleep(100);
			if (++count > 100) {
				QFAIL("Timeout");
			}
			QCoreApplication::processEvents();
		}

		// Check the result
		qWarning() << "Elapsed time: " << (count / 10.) << "s";
		QCOMPARE(update->status(), fse::UpdateManager::Status::Finished);
		QCOMPARE(spy.count(), 1);
	}
};

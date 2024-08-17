#include <QtCore/QCoreApplication>
#include <QtTest/QtTest>

#include "Dummy.hpp"
#include "TestAccessors.hpp"
#include "TestIO.hpp"
#include "TestLists.hpp"
#include "TestRefs.hpp"
#include "TestSignals.hpp"

class Tests : public QObject {
	Q_OBJECT

public:
	Tests() = default;
	virtual ~Tests() = default;

private:
	fsd::Project* _project = nullptr;

private slots:
	// Only once
	void initTestCase() {}

	// For each tests
	void init() {
		QVERIFY(!_project);
		_project = new fsd::Project(this);
		Dummy::build(_project);
	}

	void testAccessors() {
		QVERIFY(_project);
		TestAccessors(_project).run();
	}

	void testIO() {
		QVERIFY(_project);
		auto* dummy = new fsd::Project(this);
		TestIO(_project, dummy).run();
		dummy->deleteLater();
	}

	void testLists() {
		QVERIFY(_project);
		TestLists(_project).run();
	}

	void testRefs() {
		QVERIFY(_project);
		TestRefs(_project).run();
	}

	void testSignals() {
		QVERIFY(_project);
		TestSignals(_project).run();
	}

	// For each tests
	void cleanup() {
		QVERIFY(_project);
		_project->deleteLater();
		_project = nullptr;
	}

	// Only once
	void cleanupTestCase() {}
};

QTEST_MAIN(Tests)
#include "Tests.moc"

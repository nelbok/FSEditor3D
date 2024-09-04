#include <QtTest/QtTest>

#include "data/TestAccessors.hpp"
#include "data/TestIO.hpp"
#include "data/TestLists.hpp"
#include "data/TestRefs.hpp"
#include "editor/TestBalsam.hpp"

class Tests : public QObject {
	Q_OBJECT

public:
	Tests() = default;
	virtual ~Tests() = default;

private slots:
	// Only once
	void initTestCase() {}

	// For each tests
	void init() {}

	void testAccessors() {
		TestAccessors().run();
	}

	void testIO() {
		TestIO().run();
	}

	void testLists() {
		TestLists().run();
	}

	void testRefs() {
		TestRefs().run();
	}

	void testBalsam() {
		TestBalsam().run();
	}

	// For each tests
	void cleanup() {}

	// Only once
	void cleanupTestCase() {}
};

QTEST_MAIN(Tests)
#include "Tests.moc"

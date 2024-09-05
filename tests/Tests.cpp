#include <QtTest/QtTest>

#include <fse/Application.hpp>

#include "data/TestAccessors.hpp"
#include "data/TestIO.hpp"
#include "data/TestLists.hpp"
#include "data/TestRefs.hpp"

#include "editor/TestBalsam.hpp"
#include "editor/TestStyles.hpp"
#include "editor/TestTranslations.hpp"

class Tests : public QObject {
	Q_OBJECT

public:
	Tests() = default;
	virtual ~Tests() = default;

private slots:
	// Only once
	void initTestCase() {
		fse::Application::initApp(*qApp);
	}

	// For each tests
	void init() {}

	/**	DATA	**/

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

	/**	EDITOR	**/

	void testBalsam() {
		TestBalsam().run();
	}

	void testStyles() {
		TestStyles().run();
	}

	void testTranslations() {
		TestTranslations().run();
	}

	// For each tests
	void cleanup() {}

	// Only once
	void cleanupTestCase() {}
};

QTEST_MAIN(Tests)
#include "Tests.moc"

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
	~Tests() override = default;

private slots:
	void initTestCase() const {
		// Only once
		fse::Application::initApp();
	}

	void init() const {
		// For each tests
	}

	/**	DATA	**/

	void testAccessors() const {
		TestAccessors().run();
	}

	void testIO() const {
		TestIO().run();
	}

	void testLists() const {
		TestLists().run();
	}

	void testRefs() const {
		TestRefs().run();
	}

	/**	EDITOR	**/

	void testBalsam() const {
		TestBalsam().run();
	}

	void testStyles() const {
		TestStyles().run();
	}

	void testTranslations() const {
		TestTranslations().run();
	}

	void cleanup() const {
		// For each tests
	}

	void cleanupTestCase() const {
		// Only once
	}
};

QTEST_MAIN(Tests)
#include "Tests.moc"

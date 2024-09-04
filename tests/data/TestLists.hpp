#pragma once

#include <QtTest/QtTest>

#include "Dummy.hpp"
#include "TestCompare.hpp"

struct TestLists {
	void run() {
		Dummy::build(_project);
		testLinks();
		testModels();
		testObjects();
		testPlaces();
	}

private:
	fsd::Project _project;
	TestCompare _compare{ false };

	// LISTS
	void testLinks() {
		QCOMPARE(_project.links().size(), 2);
		QCOMPARE(_project.entities().size(), 10);

		auto* left = _project.createLink();
		QVERIFY(left);

		auto* right = _project.duplicateLink(left);
		_compare.testLink(left, right);

		_project.removeLink(left);
		QCOMPARE(_project.links().size(), 3);
		QCOMPARE(_project.entities().size(), 11);

		_project.cleanLinks();
		QCOMPARE(_project.links().size(), 0);
		QCOMPARE(_project.entities().size(), 8);
	}

	void testModels() {
		QCOMPARE(_project.models().size(), 3);
		QCOMPARE(_project.entities().size(), 8);

		auto* left = _project.createModel();
		QVERIFY(left);

		auto* right = _project.duplicateModel(left);
		_compare.testModel(left, right);

		_project.removeModel(left);
		QCOMPARE(_project.models().size(), 4);
		QCOMPARE(_project.entities().size(), 9);

		_project.cleanModels();
		QCOMPARE(_project.models().size(), 0);
		QCOMPARE(_project.entities().size(), 5);
	}

	void testObjects() {
		QCOMPARE(_project.objects().size(), 2);
		QCOMPARE(_project.entities().size(), 5);

		auto* left = _project.createObject();
		QVERIFY(left);

		auto* right = _project.duplicateObject(left);
		_compare.testObject(left, right);

		_project.removeObject(left);
		QCOMPARE(_project.objects().size(), 3);
		QCOMPARE(_project.entities().size(), 6);

		_project.cleanObjects();
		QCOMPARE(_project.objects().size(), 0);
		QCOMPARE(_project.entities().size(), 3);
	}

	void testPlaces() {
		QCOMPARE(_project.places().size(), 3);
		QCOMPARE(_project.entities().size(), 3);

		auto* left = _project.createPlace();
		QVERIFY(left);

		auto* right = _project.duplicatePlace(left);
		_compare.testPlace(left, right);

		_project.removePlace(left);
		QCOMPARE(_project.places().size(), 4);
		QCOMPARE(_project.entities().size(), 4);

		_project.cleanPlaces();
		QCOMPARE(_project.places().size(), 0);
		QCOMPARE(_project.entities().size(), 0);
	}
};

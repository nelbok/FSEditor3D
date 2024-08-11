#pragma once

#include <QtTest/QtTest>

#include <fsd/data/Link.hpp>
#include <fsd/data/Model.hpp>
#include <fsd/data/Object.hpp>
#include <fsd/data/Place.hpp>
#include <fsd/data/Project.hpp>

#include "TestCompare.hpp"

struct TestLists {
	TestLists(fsd::Project* project)
		: _project{ project } {}

	virtual ~TestLists() = default;

	void run() {
		QVERIFY(_project);

		testLinks();
		testModels();
		testObjects();
		testPlaces();
	}

private:
	fsd::Project* _project{ nullptr };
	TestCompare _compare{ false };

	// LISTS
	void testLinks() {
		QVERIFY(_project->links().size() == 0);
		QVERIFY(_project->entities().size() == 0);

		auto* left = _project->createLink();
		QVERIFY(left);

		auto* right = _project->duplicateLink(left);
		_compare.testLink(left, right);

		_project->removeLink(left);
		QVERIFY(_project->links().size() == 1);
		QVERIFY(_project->entities().size() == 1);

		_project->cleanLinks();
		QVERIFY(_project->links().size() == 0);
		QVERIFY(_project->entities().size() == 0);
	}

	void testModels() {
		QVERIFY(_project->models().size() == 0);
		QVERIFY(_project->entities().size() == 0);

		auto* left = _project->createModel();
		QVERIFY(left);

		auto* right = _project->duplicateModel(left);
		_compare.testModel(left, right);

		_project->removeModel(left);
		QVERIFY(_project->models().size() == 1);
		QVERIFY(_project->entities().size() == 1);

		_project->cleanModels();
		QVERIFY(_project->models().size() == 0);
		QVERIFY(_project->entities().size() == 0);
	}

	void testObjects() {
		QVERIFY(_project->objects().size() == 0);
		QVERIFY(_project->entities().size() == 0);

		auto* left = _project->createObject();
		QVERIFY(left);

		auto* right = _project->duplicateObject(left);
		_compare.testObject(left, right);

		_project->removeObject(left);
		QVERIFY(_project->objects().size() == 1);
		QVERIFY(_project->entities().size() == 1);

		_project->cleanObjects();
		QVERIFY(_project->objects().size() == 0);
		QVERIFY(_project->entities().size() == 0);
	}

	void testPlaces() {
		QVERIFY(_project->places().size() == 0);
		QVERIFY(_project->entities().size() == 0);

		auto* left = _project->createPlace();
		QVERIFY(left);

		auto* right = _project->duplicatePlace(left);
		_compare.testPlace(left, right);

		_project->removePlace(left);
		QVERIFY(_project->places().size() == 1);
		QVERIFY(_project->entities().size() == 1);

		_project->cleanPlaces();
		QVERIFY(_project->places().size() == 0);
		QVERIFY(_project->entities().size() == 0);
	}
};

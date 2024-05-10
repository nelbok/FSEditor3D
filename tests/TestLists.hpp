#pragma once

#include <QtTest/QtTest>

#include <lh/data/Link.hpp>
#include <lh/data/Project.hpp>
#include <lh/data/Place.hpp>
#include <lh/data/Player.hpp>

#include "TestCompare.hpp"

struct TestLists {
	TestLists(lh::Project* project)
		: _project{ project } {}

	virtual ~TestLists() = default;

	void run() {
		QVERIFY(_project);

		testCharacters();
		testLinks();
		testPlaces();
	}

private:
	lh::Project* _project{ nullptr };
	TestCompare _compare{ false };

	// LISTS
	void testCharacters() {
		QVERIFY(_project->characters().size() == 0);

		auto* left = _project->createCharacter();
		QVERIFY(left);

		auto* right = _project->duplicateCharacter(left);
		_compare.testCharacter(left, right);

		_project->removeCharacter(left);
		QVERIFY(_project->characters().size() == 1);

		_project->cleanCharacters();
		QVERIFY(_project->characters().size() == 0);
	}

	void testLinks() {
		QVERIFY(_project->links().size() == 0);

		auto* left = _project->createLink();
		QVERIFY(left);

		auto* right = _project->duplicateLink(left);
		_compare.testLink(left, right);

		_project->removeLink(left);
		QVERIFY(_project->links().size() == 1);

		_project->cleanLinks();
		QVERIFY(_project->links().size() == 0);
	}

	void testPlaces() {
		QVERIFY(_project->places().size() == 0);

		auto* left = _project->createPlace();
		QVERIFY(left);

		auto* right = _project->duplicatePlace(left);
		_compare.testPlace(left, right);

		_project->removePlace(left);
		QVERIFY(_project->places().size() == 1);

		_project->cleanPlaces();
		QVERIFY(_project->places().size() == 0);
	}
};

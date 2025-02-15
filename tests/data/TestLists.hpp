#pragma once

#include <QtTest/QtTest>

#include "Dummy.hpp"
#include "TestCompare.hpp"

struct TestLists {
	void run() {
		QSignalSpy spyE(&_project, &fsd::Project::entitiesUpdated);
		QSignalSpy spyL(&_project, &fsd::Project::linksUpdated);
		QSignalSpy spyM(&_project, &fsd::Project::modelsUpdated);
		QSignalSpy spyO(&_project, &fsd::Project::objectsUpdated);
		QSignalSpy spyP(&_project, &fsd::Project::placesUpdated);

		Dummy::build(_project);
		testLinks();
		testModels();
		testObjects();
		testPlaces();

		QCOMPARE(spyE.count(), 26);
		QCOMPARE(spyL.count(), 6);
		QCOMPARE(spyM.count(), 7);
		QCOMPARE(spyO.count(), 6);
		QCOMPARE(spyP.count(), 7);
	}

private:
	fsd::Project _project;
	TestCompare _compare{ false };

	// LISTS
	void testLinks() {
		auto* links = _project.links();

		QCOMPARE(links->size(), 2);
		QCOMPARE(_project.entities().size(), 10);

		auto* left = links->create();
		QVERIFY(left);

		auto* right = links->duplicate(left);
		_compare.testLink(left, right);

		links->remove(left);
		QCOMPARE(links->size(), 3);
		QCOMPARE(_project.entities().size(), 11);

		links->clean();
		QCOMPARE(links->size(), 0);
		QCOMPARE(_project.entities().size(), 8);
	}

	void testModels() {
		auto* models = _project.models();
		QCOMPARE(models->size(), 3);
		QCOMPARE(_project.entities().size(), 8);

		auto* left = models->create();
		QVERIFY(left);

		auto* right = models->duplicate(left);
		_compare.testModel(left, right);

		models->remove(left);
		QCOMPARE(models->size(), 4);
		QCOMPARE(_project.entities().size(), 9);

		models->clean();
		QCOMPARE(models->size(), 0);
		QCOMPARE(_project.entities().size(), 5);
	}

	void testObjects() {
		auto* objects = _project.objects();
		QCOMPARE(objects->size(), 2);
		QCOMPARE(_project.entities().size(), 5);

		auto* left = objects->create();
		QVERIFY(left);

		auto* right = objects->duplicate(left);
		_compare.testObject(left, right);

		objects->remove(left);
		QCOMPARE(objects->size(), 3);
		QCOMPARE(_project.entities().size(), 6);

		objects->clean();
		QCOMPARE(objects->size(), 0);
		QCOMPARE(_project.entities().size(), 3);
	}

	void testPlaces() {
		auto* places = _project.places();
		QCOMPARE(places->size(), 3);
		QCOMPARE(_project.entities().size(), 3);

		auto* left = places->create();
		QVERIFY(left);

		auto* right = places->duplicate(left);
		_compare.testPlace(left, right);

		places->remove(left);
		QCOMPARE(places->size(), 4);
		QCOMPARE(_project.entities().size(), 4);

		places->clean();
		QCOMPARE(places->size(), 0);
		QCOMPARE(_project.entities().size(), 0);
	}
};

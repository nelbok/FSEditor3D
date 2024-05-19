#pragma once

#include <QtTest/QtTest>

#include <lh/data/Character.hpp>
#include <lh/data/Link.hpp>
#include <lh/data/Project.hpp>
#include <lh/data/Place.hpp>

struct TestRefs {
	TestRefs(lh::Project* project)
		: _project{ project } {}

	virtual ~TestRefs() = default;

	void run() {
		QVERIFY(_project);

		init();
		test();
	}

private:
	lh::Project* _project{ nullptr };
	lh::Place* _place{ nullptr };
	lh::Character* _character{ nullptr };
	lh::Link* _linkA{ nullptr };
	lh::Link* _linkB{ nullptr };

	void init() {
		_place = _project->createPlace();
		_character = _project->createCharacter();
		_linkA = _project->createLink();
		_linkB = _project->createLink();

		_project->setDefaultPlace(_place);
		_character->setPlace(_place);
		_linkA->setPlace(_place);
		_linkB->setPlace(_place);
		_linkA->setLink(_linkB);
		_linkB->setLink(_linkA);
	}

	void test() {
		QVERIFY(_project->refs().size() == 0);
		QVERIFY(_place->refs().size() == 4);
		QVERIFY(_character->refs().size() == 0);
		QVERIFY(_linkA->refs().size() == 1);
		QVERIFY(_linkB->refs().size() == 1);

		_linkA->setLink(_linkA);

		QVERIFY(_linkA->refs().size() == 2);
		QVERIFY(_linkB->refs().size() == 0);
	}
};

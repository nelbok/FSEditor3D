#pragma once

#include <QtTest/QtTest>

#include <QTemporaryFile>

#include <lh/data/Link.hpp>
#include <lh/data/Project.hpp>
#include <lh/data/Place.hpp>
#include <lh/data/Player.hpp>

#include "TestCompare.hpp"

struct TestIO {
	TestIO(lh::Project* p1, lh::Project* p2)
		: _p1{ p1 }
		, _p2{ p2 } {}

	virtual ~TestIO() = default;

	void run() {
		QVERIFY(_p1);
		QVERIFY(_p2);

		reset();
		init();
		save();
		load();
		compare();
	}

private:
	lh::Project* _p1{ nullptr };
	lh::Project* _p2{ nullptr };
	QUrl _path{ "TestIO.json" };

	void init() {
		auto* p1 = _p1->createPlace();
		auto* p2 = _p1->createPlace();
		auto* p3 = _p1->createPlace();
		p1->setName("Place 1");
		p2->setName("Place 2");
		p3->setName("Place 3");

		auto* c1 = _p1->createCharacter();
		auto* c2 = _p1->createCharacter();
		c1->setName("Character 1");
		c2->setName("Character 2");
		c1->setPlace(p2);
		c2->setPlace(p3);

		auto* l1 = _p1->createLink();
		auto* l2 = _p1->createLink();
		l1->setName("Link 1");
		l2->setName("Link 2");
		l1->setLink(l2);
		l2->setLink(l1);
		l1->setPlace(p2);
		l2->setPlace(p3);

		_p1->setDefaultPlace(p2);
	}

	void reset() {
		QBENCHMARK(_p1->reset());
	}

	void save() {
		QBENCHMARK_ONCE(_p1->save(_path));
	}

	void load() {
		QBENCHMARK_ONCE(_p2->load(_path));
	}

	void compare() {
		TestCompare(true).testProject(_p1, _p2);
	}
};

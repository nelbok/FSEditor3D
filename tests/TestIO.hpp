#pragma once

#include <QtTest/QtTest>

#include <fsd/data/Link.hpp>
#include <fsd/data/Model.hpp>
#include <fsd/data/Object.hpp>
#include <fsd/data/Place.hpp>
#include <fsd/data/Project.hpp>

#include "TestCompare.hpp"

struct TestIO {
	TestIO(fsd::Project* p1, fsd::Project* p2)
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
	fsd::Project* _p1{ nullptr };
	fsd::Project* _p2{ nullptr };
	QJsonObject _json{};

	void init() {
		auto* m1 = _p1->createModel();
		auto* m2 = _p1->createModel();
		auto* m3 = _p1->createModel();
		m1->setName("Model 1");
		m2->setName("Model 2");
		m3->setName("Model 3");

		auto* p1 = _p1->createPlace();
		auto* p2 = _p1->createPlace();
		auto* p3 = _p1->createPlace();
		p1->setName("Place 1");
		p2->setName("Place 2");
		p3->setName("Place 3");
		p1->setModel(m1);
		p2->setModel(m1);
		p3->setModel(m1);

		auto* o1 = _p1->createObject();
		auto* o2 = _p1->createObject();
		o1->setName("Object 1");
		o2->setName("Object 2");
		o1->setPlace(p2);
		o2->setPlace(p3);
		o1->setModel(m2);
		o2->setModel(m2);

		auto* l1 = _p1->createLink();
		auto* l2 = _p1->createLink();
		l1->setName("Link 1");
		l2->setName("Link 2");
		l1->setLink(l2);
		l2->setLink(l1);
		l1->setPlace(p2);
		l2->setPlace(p3);
		l1->setModel(m3);
		l2->setModel(m3);

		_p1->setDefaultPlace(p2);
	}

	void reset() {
		QBENCHMARK(_p1->reset());
	}

	void save() {
		QBENCHMARK(_p1->save(_json));
	}

	void load() {
		QBENCHMARK(_p2->load(_json));
	}

	void compare() {
		TestCompare(true).testProject(_p1, _p2);
	}
};

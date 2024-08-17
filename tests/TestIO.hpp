#pragma once

#include <QtTest/QtTest>

#include "Dummy.hpp"
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

		Dummy::build(_p1);

		save();
		load();
		compare();
	}

private:
	fsd::Project* _p1{ nullptr };
	fsd::Project* _p2{ nullptr };
	QJsonObject _json{};

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

#pragma once

#include <QtTest/QtTest>

#include "Dummy.hpp"
#include "TestCompare.hpp"

struct TestIO {
	void run() {
		Dummy::build(_p1);
		reset();
		Dummy::build(_p1);
		save();
		load();
		compare();
	}

private:
	fsd::Project _p1;
	fsd::Project _p2;
	QJsonObject _json{};

	void reset() {
		QBENCHMARK(_p1.reset());
	}

	void save() {
		QBENCHMARK(_p1.save(_json));
	}

	void load() {
		QBENCHMARK(_p2.load(_json));
	}

	void compare() {
		TestCompare(true).testProject(&_p1, &_p2);
	}
};

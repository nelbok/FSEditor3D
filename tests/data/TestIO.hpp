#pragma once

#include <QtTest/QtTest>

#include <fsd/io/Json.hpp>
#include <fsd/io/JsonException.hpp>

#include "Dummy.hpp"
#include "TestCompare.hpp"

struct TestIO {
	void run() {
		QVERIFY_THROWS_EXCEPTION(fsd::JsonException, fsd::Json::toValue({}, {}, {}));
		QVERIFY_THROWS_EXCEPTION(fsd::JsonException, fsd::Json::toObject({}, {}, {}));
		QVERIFY_THROWS_EXCEPTION(fsd::JsonException, fsd::Json::toArray({}, {}, {}));
		QVERIFY_THROWS_EXCEPTION(fsd::JsonException, fsd::Json::toString({}, {}, {}));
		QVERIFY_THROWS_EXCEPTION(fsd::JsonException, fsd::Json::toInt({}, {}, {}));
		QVERIFY_THROWS_EXCEPTION(fsd::JsonException, fsd::Json::toDouble({}, {}, {}));
		QVERIFY_THROWS_EXCEPTION(fsd::JsonException, fsd::Json::toBool({}, {}, {}));
		QVERIFY_THROWS_EXCEPTION(fsd::JsonException, fsd::Json::toUrl({}, {}, {}));
		QVERIFY_THROWS_EXCEPTION(fsd::JsonException, fsd::Json::toUuid({}, {}, {}));
		QVERIFY_THROWS_EXCEPTION(fsd::JsonException, fsd::Json::toColor({}, {}, {}));
		QVERIFY_THROWS_EXCEPTION(fsd::JsonException, fsd::Json::toVector2D({}, {}, {}));
		QVERIFY_THROWS_EXCEPTION(fsd::JsonException, fsd::Json::toVector3D({}, {}, {}));

		Dummy::build(_p1);
		reset();
		Dummy::build(_p1);
		save();
		load();
		compare();
		checkSignals();
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

	void checkSignals() {
		QSignalSpy spyE(&_p2, &fsd::Project::entitiesUpdated);
		QSignalSpy spyL(&_p2, &fsd::Project::linksUpdated);
		QSignalSpy spyM(&_p2, &fsd::Project::modelsUpdated);
		QSignalSpy spyO(&_p2, &fsd::Project::objectsUpdated);
		QSignalSpy spyP(&_p2, &fsd::Project::placesUpdated);

		_p2.load(_json);

		QCOMPARE(spyE.count(), 1);
		QCOMPARE(spyL.count(), 1);
		QCOMPARE(spyM.count(), 1);
		QCOMPARE(spyO.count(), 1);
		QCOMPARE(spyP.count(), 1);
	}
};

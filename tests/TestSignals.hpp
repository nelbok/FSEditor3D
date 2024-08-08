#pragma once

#include <QtTest/QtTest>

#include <fsd/data/Link.hpp>
#include <fsd/data/Object.hpp>
#include <fsd/data/Project.hpp>
#include <fsd/data/Place.hpp>

struct TestSignals {
	TestSignals(fsd::Project* project)
		: _project{ project } {}

	virtual ~TestSignals() = default;

	void run() {
		QVERIFY(_project);

		qWarning("Test signals not implemented yet. Skipping...");
	}

private:
	fsd::Project* _project{ nullptr };
};

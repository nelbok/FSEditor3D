#pragma once

#include <QtTest/QtTest>

#include <lh/data/Character.hpp>
#include <lh/data/Link.hpp>
#include <lh/data/Project.hpp>
#include <lh/data/Place.hpp>

struct TestSignals {
	TestSignals(lh::Project* project)
		: _project{ project } {}

	virtual ~TestSignals() = default;

	void run() {
		QVERIFY(_project);

		qWarning("Test signals not implemented yet. Skipping...");
	}

private:
	lh::Project* _project{ nullptr };
};

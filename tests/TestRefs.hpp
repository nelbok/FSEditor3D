#pragma once

#include <QtTest/QtTest>

#include <fsd/data/Link.hpp>
#include <fsd/data/Object.hpp>
#include <fsd/data/Project.hpp>
#include <fsd/data/Place.hpp>

struct TestRefs {
	TestRefs(fsd::Project* project)
		: _project{ project } {}

	virtual ~TestRefs() = default;

	void run() {
		QVERIFY(_project);

		init();
		test();
	}

private:
	fsd::Project* _project{ nullptr };
	fsd::Model* _model{ nullptr };
	fsd::Place* _place{ nullptr };
	fsd::Object* _object{ nullptr };
	fsd::Link* _linkA{ nullptr };
	fsd::Link* _linkB{ nullptr };

	void init() {
		_model = _project->createModel();
		_place = _project->createPlace();
		_object = _project->createObject();
		_linkA = _project->createLink();
		_linkB = _project->createLink();

		_project->setDefaultPlace(_place);
		_place->setModel(_model);
		_object->setPlace(_place);
		_object->setModel(_model);
		_linkA->setPlace(_place);
		_linkB->setPlace(_place);
		_linkA->setModel(_model);
		_linkB->setModel(_model);
		_linkA->setLink(_linkB);
		_linkB->setLink(_linkA);
	}

	void test() {
		QVERIFY(_project->refs().size() == 0);
		QVERIFY(_model->refs().size() == 4);
		QVERIFY(_place->refs().size() == 4);
		QVERIFY(_object->refs().size() == 0);
		QVERIFY(_linkA->refs().size() == 1);
		QVERIFY(_linkB->refs().size() == 1);

		_linkA->setLink(_linkA);

		QVERIFY(_linkA->refs().size() == 2);
		QVERIFY(_linkB->refs().size() == 0);
	}
};

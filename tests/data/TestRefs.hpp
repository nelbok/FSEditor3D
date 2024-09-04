#pragma once

#include <QtTest/QtTest>

#include "Dummy.hpp"

struct TestRefs {
	void run() {
		Dummy::build(_project);
		init();
		test();
	}

private:
	fsd::Project _project;
	fsd::Model* _model{ nullptr };
	fsd::Place* _place{ nullptr };
	fsd::Object* _object{ nullptr };
	fsd::Link* _linkA{ nullptr };
	fsd::Link* _linkB{ nullptr };

	void init() {
		_model = _project.models().at(0);
		_place = _project.places().at(0);
		_object = _project.objects().at(0);
		_linkA = _project.links().at(0);
		_linkB = _project.links().at(1);
	}

	void test() {
		QCOMPARE(_project.refs().size(), 0);
		QCOMPARE(_model->refs().size(), 3);
		QCOMPARE(_place->refs().size(), 1);
		QCOMPARE(_object->refs().size(), 0);
		QCOMPARE(_linkA->refs().size(), 1);
		QCOMPARE(_linkB->refs().size(), 1);

		_linkA->setLink(_linkA);

		QCOMPARE(_linkA->refs().size(), 2);
		QCOMPARE(_linkB->refs().size(), 0);
	}
};

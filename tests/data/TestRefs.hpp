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
	fsd::EntryPoint* _entryPoint{ nullptr };
	fsd::Model* _model{ nullptr };
	fsd::Place* _placeA{ nullptr };
	fsd::Place* _placeB{ nullptr };
	fsd::Place* _placeC{ nullptr };
	fsd::Object* _object{ nullptr };
	fsd::Link* _linkA{ nullptr };
	fsd::Link* _linkB{ nullptr };

	void init() {
		_model = _project.models()->at(0);
		_placeA = _project.places()->at(0);
		_placeB = _project.places()->at(1);
		_placeC = _project.places()->at(2);
		_object = _project.objects()->at(0);
		_linkA = _project.links()->at(0);
		_linkB = _project.links()->at(1);
		_entryPoint = _project.entryPoints()->at(0);
	}

	void test() {
		QCOMPARE(_project.refs().size(), 0);
		QCOMPARE(_model->refs().size(), 3);
		QCOMPARE(_placeA->refs().size(), 1);
		QCOMPARE(_placeB->refs().size(), 3);
		QCOMPARE(_placeC->refs().size(), 3);
		QCOMPARE(_object->refs().size(), 0);
		QCOMPARE(_linkA->refs().size(), 1);
		QCOMPARE(_linkB->refs().size(), 1);
		QCOMPARE(_entryPoint->refs().size(), 0);

		_linkA->setLink(_linkA);

		QCOMPARE(_linkA->refs().size(), 2);
		QCOMPARE(_linkB->refs().size(), 0);
	}
};

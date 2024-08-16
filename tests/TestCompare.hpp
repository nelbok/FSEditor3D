#pragma once

#include <QtTest/QtTest>

#include <fsd/data/Link.hpp>
#include <fsd/data/Model.hpp>
#include <fsd/data/Object.hpp>
#include <fsd/data/Place.hpp>
#include <fsd/data/Project.hpp>

struct TestCompare {
	TestCompare(bool isSame)
		: _isSame{ isSame } {}

	virtual ~TestCompare() = default;

	void testEntity(fsd::Entity* left, fsd::Entity* right) {
		if (_isSame) {
			QCOMPARE(left->uuid(), right->uuid());
			QCOMPARE(left->name(), right->name());
		} else {
			QVERIFY(left->uuid() != right->uuid());
			QVERIFY(left->name() + "*" == right->name());
		}
	}

	void testLink(fsd::Link* left, fsd::Link* right) {
		testPlacement(left, right);

		testUuidPointer(left->link(), right->link());
	}

	void testModel(fsd::Model* left, fsd::Model* right) {
		testEntity(left, right);

		QCOMPARE(left->sourcePath(), right->sourcePath());
		QCOMPARE(left->qmlName(), right->qmlName());
		QCOMPARE(left->modelType(), right->modelType());
	}

	void testObject(fsd::Object* left, fsd::Object* right) {
		testPlacement(left, right);
	}

	void testPlace(fsd::Place* left, fsd::Place* right) {
		testShape(left, right);
	}

	void testPlacement(fsd::Placement* left, fsd::Placement* right) {
		testShape(left, right);

		QCOMPARE(left->localPosition(), right->localPosition());
		QCOMPARE(left->localRotation(), right->localRotation());
		testUuidPointer(left->place(), right->place());
	}

	void testShape(fsd::Shape* left, fsd::Shape* right) {
		testEntity(left, right);

		testUuidPointer(left->model(), right->model());
	}

	void testProject(fsd::Project* left, fsd::Project* right) {
		testEntity(left, right);

		testUuidPointer(left->defaultPlace(), right->defaultPlace());

		testProjectList(left->objects(), right->objects(), &TestCompare::testObject);
		testProjectList(left->links(), right->links(), &TestCompare::testLink);
		testProjectList(left->models(), right->models(), &TestCompare::testModel);
		testProjectList(left->places(), right->places(), &TestCompare::testPlace);
		testProjectList(left->entities(), right->entities(), &TestCompare::testEntity);
	}

	void testUuidPointer(fsd::Entity* left, fsd::Entity* right) {
		bool isLeftValid = left != nullptr;
		bool isRightValid = right != nullptr;
		QCOMPARE(isLeftValid, isRightValid);
		if (isLeftValid && isRightValid)
			QCOMPARE(left->uuid(), right->uuid());
	}

private:
	template<class TClass>
	void testProjectList(QList<TClass*> left, QList<TClass*> right, void (TestCompare::*func)(TClass*, TClass*)) {
		auto compare = [](TClass* a, TClass* b) {
			return a->uuid() < b->uuid();
		};
		std::sort(left.begin(), left.end(), compare);
		std::sort(right.begin(), right.end(), compare);
		QCOMPARE(left.size(), right.size());
		for (qsizetype i = 0; i < left.size(); ++i) {
			(this->*func)(left.at(i), right.at(i));
		}
	}

private:
	bool _isSame{ true };
};

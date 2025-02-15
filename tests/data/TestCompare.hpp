#pragma once

#include <QtTest/QtTest>

#include <fsd/data/EntryPoint.hpp>
#include <fsd/data/Link.hpp>
#include <fsd/data/Model.hpp>
#include <fsd/data/Object.hpp>
#include <fsd/data/Place.hpp>
#include <fsd/data/Project.hpp>

struct TestCompare {
	explicit TestCompare(bool isSame)
		: _isSame{ isSame } {}

	void testEntity(const fsd::Entity* left, const fsd::Entity* right) const {
		if (_isSame) {
			QCOMPARE(left->uuid(), right->uuid());
			QCOMPARE(left->name(), right->name());
		} else {
			QVERIFY(left->uuid() != right->uuid());
			QVERIFY(left->name() + "*" == right->name());
		}
	}

	void testEntryPoint(const fsd::EntryPoint* left, const fsd::EntryPoint* right) const {
		testEntity(left, right);

		QCOMPARE(left->position(), right->position());
		QCOMPARE(left->rotation(), right->rotation());

		testUuidPointer(left->place(), right->place());
	}

	void testGeometry(const fsd::Geometry* left, const fsd::Geometry* right) const {
		testEntity(left, right);

		QCOMPARE(left->localPosition(), right->localPosition());
		QCOMPARE(left->localRotation(), right->localRotation());
		QCOMPARE(left->localScale(), right->localScale());

		QCOMPARE(left->globalPosition(), right->globalPosition());
		QCOMPARE(left->globalRotation(), right->globalRotation());
		QCOMPARE(left->globalScale(), right->globalScale());
	}

	void testLink(const fsd::Link* left, const fsd::Link* right) const {
		testPlacement(left, right);

		testUuidPointer(left->link(), right->link());
	}

	void testModel(const fsd::Model* left, const fsd::Model* right) const {
		testGeometry(left, right);

		QCOMPARE(left->sourcePath(), right->sourcePath());
		QCOMPARE(left->qmlName(), right->qmlName());
		QCOMPARE(left->modelType(), right->modelType());
	}

	void testObject(const fsd::Object* left, const fsd::Object* right) const {
		testPlacement(left, right);
	}

	void testPlace(const fsd::Place* left, const fsd::Place* right) const {
		testShape(left, right);
	}

	void testPlacement(const fsd::Placement* left, const fsd::Placement* right) const {
		testShape(left, right);

		testUuidPointer(left->place(), right->place());
	}

	void testShape(const fsd::Shape* left, const fsd::Shape* right) const {
		testGeometry(left, right);

		testUuidPointer(left->model(), right->model());
	}

	void testProject(const fsd::Project* left, const fsd::Project* right) const {
		testGeometry(left, right);

		testUuidPointer(left->defaultPlace(), right->defaultPlace());

		testProjectList<fsd::EntryPoint>(left->entryPoints()->get(), right->entryPoints()->get(), &TestCompare::testEntryPoint);
		testProjectList<fsd::Object>(left->objects()->get(), right->objects()->get(), &TestCompare::testObject);
		testProjectList<fsd::Link>(left->links()->get(), right->links()->get(), &TestCompare::testLink);
		testProjectList<fsd::Model>(left->models()->get(), right->models()->get(), &TestCompare::testModel);
		testProjectList<fsd::Place>(left->places()->get(), right->places()->get(), &TestCompare::testPlace);
		testProjectList<fsd::Entity>(left->entities(), right->entities(), &TestCompare::testEntity);
	}

	void testUuidPointer(const fsd::Entity* left, const fsd::Entity* right) const {
		bool isLeftValid = left != nullptr;
		bool isRightValid = right != nullptr;
		QCOMPARE(isLeftValid, isRightValid);
		if (!isLeftValid || !isRightValid)
			return;
		QCOMPARE(left->uuid(), right->uuid());
	}

private:
	template<class TClass>
	void testProjectList(QList<TClass*> left, QList<TClass*> right, std::function<void(const TestCompare*, const TClass*, const TClass*)> func) const {
		auto compare = [](TClass* a, TClass* b) {
			return a->uuid() < b->uuid();
		};
		std::sort(left.begin(), left.end(), compare);
		std::sort(right.begin(), right.end(), compare);
		QCOMPARE(left.size(), right.size());
		for (qsizetype i = 0; i < left.size(); ++i) {
			func(this, left.at(i), right.at(i));
		}
	}

private:
	bool _isSame{ true };
};

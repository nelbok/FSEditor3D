#pragma once

#include <QtTest/QtTest>

#include <lh/data/Character.hpp>
#include <lh/data/Link.hpp>
#include <lh/data/Project.hpp>
#include <lh/data/Place.hpp>

struct TestCompare {
	TestCompare(bool isSame)
		: _isSame{ isSame } {}

	virtual ~TestCompare() = default;

	void testCharacter(lh::Character* left, lh::Character* right) {
		testPlacement(left, right);

		QCOMPARE(left->hair(), right->hair());
		QCOMPARE(left->skin(), right->skin());
		QCOMPARE(left->clothes(), right->clothes());
		QCOMPARE(left->height(), right->height());
		QCOMPARE(left->species(), right->species());
		QCOMPARE(left->gender(), right->gender());
	}

	void testEntity(lh::Entity* left, lh::Entity* right) {
		if (_isSame) {
			QCOMPARE(left->uuid(), right->uuid());
			QCOMPARE(left->name(), right->name());
		} else {
			QVERIFY(left->uuid() != right->uuid());
			QVERIFY(left->name() + "*" == right->name());
		}
	}

	void testLink(lh::Link* left, lh::Link* right) {
		testPlacement(left, right);

		testUuidPointer(left->link(), right->link());
	}

	void testPlace(lh::Place* left, lh::Place* right) {
		testEntity(left, right);
	}

	void testPlacement(lh::Placement* left, lh::Placement* right) {
		testEntity(left, right);

		QCOMPARE(left->position(), right->position());
		QCOMPARE(left->rotation(), right->rotation());
		testUuidPointer(left->place(), right->place());
	}

	void testProject(lh::Project* left, lh::Project* right) {
		testEntity(left, right);

		testUuidPointer(left->defaultPlace(), right->defaultPlace());

		{
			const auto& ll = left->characters();
			const auto& rl = right->characters();
			QCOMPARE(ll.size(), rl.size());
			for (qsizetype i = 0; i < ll.size(); ++i) {
				testCharacter(ll.at(i), rl.at(i));
			}
		}

		{
			const auto& ll = left->links();
			const auto& rl = right->links();
			QCOMPARE(ll.size(), rl.size());
			for (qsizetype i = 0; i < ll.size(); ++i) {
				testLink(ll.at(i), rl.at(i));
			}
		}

		{
			const auto& ll = left->places();
			const auto& rl = right->places();
			QCOMPARE(ll.size(), rl.size());
			for (qsizetype i = 0; i < ll.size(); ++i) {
				testPlace(ll.at(i), rl.at(i));
			}
		}
	}

	void testUuidPointer(lh::Entity* left, lh::Entity* right) {
		bool isLeftValid = left != nullptr;
		bool isRightValid = right != nullptr;
		QCOMPARE(isLeftValid, isRightValid);
		if (isLeftValid && isRightValid)
			QCOMPARE(left->uuid(), right->uuid());
	}

private:
	bool _isSame{ true };
};

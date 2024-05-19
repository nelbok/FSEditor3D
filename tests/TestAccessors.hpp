#pragma once

#include <QtTest/QtTest>

#include <lh/data/Character.hpp>
#include <lh/data/Link.hpp>
#include <lh/data/Project.hpp>
#include <lh/data/Place.hpp>

struct TestAccessors {
	TestAccessors(lh::Project* project)
		: _project{ project } {}

	virtual ~TestAccessors() = default;

	void run() {
		QVERIFY(_project);
		auto* character = _project->createCharacter();
		auto* link = _project->createLink();
		auto* place = _project->createPlace();

		testCharacter(character, character->metaObject());
		testLink(link, link->metaObject());
		testPlace(place, place->metaObject());
		testProject(_project, _project->metaObject());
	}

private:
	lh::Project* _project{ nullptr };

	void testCharacter(lh::Character* character, const QMetaObject* metaObject) {
		testPlacement(character, metaObject->superClass());

		const auto hair = QColor("blue");
		character->setHair(hair);
		QCOMPARE(character->hair(), hair);

		const auto skin = QColor("white");
		character->setSkin(skin);
		QCOMPARE(character->skin(), skin);

		const auto clothes = QColor("red");
		character->setClothes(clothes);
		QCOMPARE(character->clothes(), clothes);

		const auto height = 177;
		character->setHeight(height);
		QCOMPARE(character->height(), height);

		const auto species = lh::Character::Species::Bun;
		character->setSpecies(species);
		QCOMPARE(character->species(), species);

		const auto gender = lh::Character::Gender::Female;
		character->setGender(gender);
		QCOMPARE(character->gender(), gender);

		QCOMPARE(metaObject->propertyCount(), 12);
		QCOMPARE(metaObject->propertyOffset(), 6);
	}

	void testEntity(lh::Entity* entity, const QMetaObject* metaObject) {
		QCOMPARE(metaObject->propertyCount(), 3);
		QCOMPARE(metaObject->propertyOffset(), 1);

		const auto name = QString("Test");
		entity->setName(name);
		QCOMPARE(entity->name(), name);
	}

	void testLink(lh::Link* link, const QMetaObject* metaObject) {
		testPlacement(link, metaObject->superClass());

		auto* linkA = _project->links().at(0);
		link->setLink(linkA);
		QCOMPARE(link->link(), linkA);

		QCOMPARE(metaObject->propertyCount(), 7);
		QCOMPARE(metaObject->propertyOffset(), 6);
	}

	void testPlace(lh::Place* place, const QMetaObject* metaObject) {
		testEntity(place, metaObject->superClass());

		QCOMPARE(metaObject->propertyCount(), 3);
		QCOMPARE(metaObject->propertyOffset(), 3);
	}

	void testPlacement(lh::Placement* placement, const QMetaObject* metaObject) {
		testEntity(placement, metaObject->superClass());

		const auto position = QVector3D(0, 0, 0);
		placement->setPosition(position);
		QCOMPARE(placement->position(), position);

		const auto rotation = QVector3D(0, 0, 0);
		placement->setRotation(rotation);
		QCOMPARE(placement->rotation(), rotation);

		auto* place = _project->places().at(0);
		placement->setPlace(place);
		QCOMPARE(placement->place(), place);

		QCOMPARE(metaObject->propertyCount(), 6);
		QCOMPARE(metaObject->propertyOffset(), 3);
	}

	void testProject(lh::Project* project, const QMetaObject* metaObject) {
		testEntity(project, metaObject->superClass());

		QCOMPARE(metaObject->propertyCount(), 8);
		QCOMPARE(metaObject->propertyOffset(), 3);

		const auto path = QUrl(":/test/img");
		project->setPath(path);
		QCOMPARE(project->path(), path);

		auto* place = _project->places().at(0);
		project->setDefaultPlace(place);
		QCOMPARE(project->defaultPlace(), place);

		QCOMPARE(project->characters().count(), 1);
		QCOMPARE(project->places().count(), 1);
		QCOMPARE(project->links().count(), 1);
	}
};

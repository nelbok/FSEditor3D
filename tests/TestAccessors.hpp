#pragma once

#include <QtTest/QtTest>

#include <fsd/data/Character.hpp>
#include <fsd/data/Link.hpp>
#include <fsd/data/Model.hpp>
#include <fsd/data/Place.hpp>
#include <fsd/data/Project.hpp>

struct TestAccessors {
	TestAccessors(fsd::Project* project)
		: _project{ project } {}

	virtual ~TestAccessors() = default;

	void run() {
		QVERIFY(_project);
		_project->reset();
		auto* character = _project->createCharacter();
		auto* link = _project->createLink();
		auto* model = _project->createModel();
		auto* place = _project->createPlace();

		testCharacter(character, character->metaObject());
		testLink(link, link->metaObject());
		testModel(model, model->metaObject());
		testPlace(place, place->metaObject());
		testProject(_project, _project->metaObject());
	}

private:
	fsd::Project* _project{ nullptr };

	void testCharacter(fsd::Character* character, const QMetaObject* metaObject) {
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

		const auto species = fsd::Character::Species::Bun;
		character->setSpecies(species);
		QCOMPARE(character->species(), species);

		const auto gender = fsd::Character::Gender::Female;
		character->setGender(gender);
		QCOMPARE(character->gender(), gender);

		QCOMPARE(metaObject->propertyCount(), 15);
		QCOMPARE(metaObject->propertyOffset(), 9);
	}

	void testEntity(fsd::Entity* entity, const QMetaObject* metaObject) {
		QCOMPARE(metaObject->propertyCount(), 5);
		QCOMPARE(metaObject->propertyOffset(), 1);

		const auto name = QString("Test");
		entity->setName(name);
		QCOMPARE(entity->name(), name);

		const auto isAlive = false;
		entity->setIsAlive(isAlive);
		QCOMPARE(entity->isAlive(), isAlive);
	}

	void testLink(fsd::Link* link, const QMetaObject* metaObject) {
		testPlacement(link, metaObject->superClass());

		auto* linkA = _project->links().at(0);
		link->setLink(linkA);
		QCOMPARE(link->link(), linkA);

		QCOMPARE(metaObject->propertyCount(), 10);
		QCOMPARE(metaObject->propertyOffset(), 9);
	}

	void testModel(fsd::Model* model, const QMetaObject* metaObject) {
		testEntity(model, metaObject->superClass());

		const auto path = QUrl(":/test/img");
		model->setSourcePath(path);
		QCOMPARE(model->sourcePath(), path);

		const auto name = ":/test/img";
		model->setQmlName(name);
		QCOMPARE(model->qmlName(), name);

		const auto type = fsd::Model::Type::Link;
		model->setType(type);
		QCOMPARE(model->type(), type);

		QCOMPARE(metaObject->propertyCount(), 8);
		QCOMPARE(metaObject->propertyOffset(), 5);
	}

	void testObject(fsd::Object* object, const QMetaObject* metaObject) {
		testEntity(object, metaObject->superClass());

		auto* model = _project->models().at(0);
		object->setModel(model);
		QCOMPARE(object->model(), model);

		QCOMPARE(metaObject->propertyCount(), 6);
		QCOMPARE(metaObject->propertyOffset(), 5);
	}

	void testPlace(fsd::Place* place, const QMetaObject* metaObject) {
		testObject(place, metaObject->superClass());

		QCOMPARE(metaObject->propertyCount(), 6);
		QCOMPARE(metaObject->propertyOffset(), 6);
	}

	void testPlacement(fsd::Placement* placement, const QMetaObject* metaObject) {
		testObject(placement, metaObject->superClass());

		const auto position = QVector3D(0, 0, 0);
		placement->setPosition(position);
		QCOMPARE(placement->position(), position);

		const auto rotation = QVector3D(0, 0, 0);
		placement->setRotation(rotation);
		QCOMPARE(placement->rotation(), rotation);

		auto* place = _project->places().at(0);
		placement->setPlace(place);
		QCOMPARE(placement->place(), place);

		QCOMPARE(metaObject->propertyCount(), 9);
		QCOMPARE(metaObject->propertyOffset(), 6);
	}

	void testProject(fsd::Project* project, const QMetaObject* metaObject) {
		testEntity(project, metaObject->superClass());

		QCOMPARE(metaObject->propertyCount(), 10);
		QCOMPARE(metaObject->propertyOffset(), 5);

		auto* place = _project->places().at(0);
		project->setDefaultPlace(place);
		QCOMPARE(project->defaultPlace(), place);

		QCOMPARE(project->characters().count(), 1);
		QCOMPARE(project->links().count(), 1);
		QCOMPARE(project->models().count(), 1);
		QCOMPARE(project->places().count(), 1);
	}
};

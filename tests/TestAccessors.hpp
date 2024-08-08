#pragma once

#include <QtTest/QtTest>

#include <fsd/data/Link.hpp>
#include <fsd/data/Model.hpp>
#include <fsd/data/Object.hpp>
#include <fsd/data/Place.hpp>
#include <fsd/data/Project.hpp>

struct TestAccessors {
	TestAccessors(fsd::Project* project)
		: _project{ project } {}

	virtual ~TestAccessors() = default;

	void run() {
		QVERIFY(_project);
		_project->reset();
		auto* link = _project->createLink();
		auto* model = _project->createModel();
		auto* place = _project->createPlace();
		auto* object = _project->createObject();

		testLink(link, link->metaObject());
		testModel(model, model->metaObject());
		testObject(object, object->metaObject());
		testPlace(place, place->metaObject());
		testProject(_project, _project->metaObject());
	}

private:
	fsd::Project* _project{ nullptr };

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
		testPlacement(object, metaObject->superClass());

		QCOMPARE(metaObject->propertyCount(), 9);
		QCOMPARE(metaObject->propertyOffset(), 9);
	}

	void testPlace(fsd::Place* place, const QMetaObject* metaObject) {
		testShape(place, metaObject->superClass());

		QCOMPARE(metaObject->propertyCount(), 6);
		QCOMPARE(metaObject->propertyOffset(), 6);
	}

	void testPlacement(fsd::Placement* placement, const QMetaObject* metaObject) {
		testShape(placement, metaObject->superClass());

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

	void testShape(fsd::Shape* shape, const QMetaObject* metaObject) {
		testEntity(shape, metaObject->superClass());

		auto* model = _project->models().at(0);
		shape->setModel(model);
		QCOMPARE(shape->model(), model);

		QCOMPARE(metaObject->propertyCount(), 6);
		QCOMPARE(metaObject->propertyOffset(), 5);
	}

	void testProject(fsd::Project* project, const QMetaObject* metaObject) {
		testEntity(project, metaObject->superClass());

		QCOMPARE(metaObject->propertyCount(), 10);
		QCOMPARE(metaObject->propertyOffset(), 5);

		auto* place = _project->places().at(0);
		project->setDefaultPlace(place);
		QCOMPARE(project->defaultPlace(), place);

		QCOMPARE(project->links().count(), 1);
		QCOMPARE(project->models().count(), 1);
		QCOMPARE(project->objects().count(), 1);
		QCOMPARE(project->places().count(), 1);
	}
};

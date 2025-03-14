#pragma once

#include <QtTest/QtTest>

#include "Dummy.hpp"

struct TestAccessors {
	void run() {
		Dummy::build(_project);

		auto* entryPoint = _project.entryPoints()->at(0);
		auto* link = _project.links()->at(0);
		auto* model = _project.models()->at(0);
		auto* place = _project.places()->at(0);
		auto* object = _project.objects()->at(0);

		// Tests
		testEntryPoint(entryPoint, entryPoint->metaObject());
		testLink(link, link->metaObject());
		testModel(model, model->metaObject());
		testObject(object, object->metaObject());
		testPlace(place, place->metaObject());
		testProject(&_project, _project.metaObject());
	}

private:
	fsd::Project _project;

	void testEntity(fsd::Entity* entity, const QMetaObject* metaObject) const {
		const auto name = QString("Test");
		entity->setName(name);
		QCOMPARE(entity->name(), name);

		const auto isAlive = false;
		entity->setIsAlive(isAlive);
		QCOMPARE(entity->isAlive(), isAlive);

		QCOMPARE(metaObject->propertyCount(), 6);
		QCOMPARE(metaObject->propertyOffset(), 1);
	}

	void testEntryPoint(fsd::EntryPoint* entryPoint, const QMetaObject* metaObject) const {
		testEntity(entryPoint, metaObject->superClass());

		QCOMPARE(entryPoint->position(), QVector3D(10, 10, 10));
		QCOMPARE(entryPoint->rotation(), 10.f);

		auto* place = _project.places()->at(0);
		entryPoint->setPlace(place);
		QCOMPARE(entryPoint->place(), place);

		QCOMPARE(metaObject->propertyCount(), 9);
		QCOMPARE(metaObject->propertyOffset(), 6);
	}

	void testGeometry(fsd::Geometry* geometry, const QMetaObject* metaObject) const {
		testEntity(geometry, metaObject->superClass());

		QCOMPARE(geometry->localPosition(), QVector3D(10, 10, 10));
		QCOMPARE(geometry->localRotation(), QVector3D(10, 10, 10));
		QCOMPARE(geometry->localScale(), QVector3D(10, 10, 10));

		QCOMPARE(metaObject->propertyCount(), 12);
		QCOMPARE(metaObject->propertyOffset(), 6);
	}

	void testLink(fsd::Link* link, const QMetaObject* metaObject) const {
		testPlacement(link, metaObject->superClass());

		auto* linkA = _project.links()->at(0);
		link->setLink(linkA);
		QCOMPARE(link->link(), linkA);

		QCOMPARE(metaObject->propertyCount(), 15);
		QCOMPARE(metaObject->propertyOffset(), 14);
	}

	void testModel(fsd::Model* model, const QMetaObject* metaObject) const {
		testGeometry(model, metaObject->superClass());

		const auto path = QUrl(":/test/img");
		model->setSourcePath(path);
		QCOMPARE(model->sourcePath(), path);

		const auto name = ":/test/img";
		model->setQmlName(name);
		QCOMPARE(model->qmlName(), name);

		// Use QVERIFY_THROWS_EXCEPTION
		//const auto modelType = fsd::Model::ModelType::Link;
		//model->setModelType(modelType);
		//QCOMPARE(model->modelType(), modelType);

		QCOMPARE(model->globalPosition(), QVector3D(20, 20, 20));
		QCOMPARE(model->globalRotation(), QVector3D(20, 20, 20));
		QCOMPARE(model->globalScale(), QVector3D(100, 100, 100));

		QCOMPARE(metaObject->propertyCount(), 15);
		QCOMPARE(metaObject->propertyOffset(), 12);
	}

	void testObject(fsd::Object* object, const QMetaObject* metaObject) const {
		testPlacement(object, metaObject->superClass());

		QCOMPARE(metaObject->propertyCount(), 14);
		QCOMPARE(metaObject->propertyOffset(), 14);
	}

	void testPlace(fsd::Place* place, const QMetaObject* metaObject) const {
		testShape(place, metaObject->superClass());

		QCOMPARE(metaObject->propertyCount(), 13);
		QCOMPARE(metaObject->propertyOffset(), 13);
	}

	void testPlacement(fsd::Placement* placement, const QMetaObject* metaObject) const {
		testShape(placement, metaObject->superClass());

		auto* place = _project.places()->at(0);
		placement->setPlace(place);
		QCOMPARE(placement->place(), place);

		QCOMPARE(metaObject->propertyCount(), 14);
		QCOMPARE(metaObject->propertyOffset(), 13);
	}

	void testProject(fsd::Project* project, const QMetaObject* metaObject) const {
		testGeometry(project, metaObject->superClass());

		auto* place = _project.places()->at(0);
		project->setDefaultPlace(place);
		QCOMPARE(project->defaultPlace(), place);

		QCOMPARE(project->entryPoints()->size(), 2);
		QCOMPARE(project->links()->size(), 2);
		QCOMPARE(project->models()->size(), 3);
		QCOMPARE(project->objects()->size(), 2);
		QCOMPARE(project->places()->size(), 3);
		QCOMPARE(project->entities().size(), 12);

		QCOMPARE(project->globalPosition(), QVector3D(10, 10, 10));
		QCOMPARE(project->globalRotation(), QVector3D(10, 10, 10));
		QCOMPARE(project->globalScale(), QVector3D(10, 10, 10));

		QCOMPARE(metaObject->propertyCount(), 19);
		QCOMPARE(metaObject->propertyOffset(), 12);
	}

	void testShape(fsd::Shape* shape, const QMetaObject* metaObject) const {
		testGeometry(shape, metaObject->superClass());

		// Use QVERIFY_THROWS_EXCEPTION
		auto* model = shape->model();
		shape->setModel(nullptr);
		QCOMPARE(shape->model(), nullptr);
		shape->setModel(model);
		QCOMPARE(shape->model(), model);

		QCOMPARE(shape->globalPosition(), QVector3D(30, 30, 30));
		QCOMPARE(shape->globalRotation(), QVector3D(30, 30, 30));
		QCOMPARE(shape->globalScale(), QVector3D(1000, 1000, 1000));

		QCOMPARE(metaObject->propertyCount(), 13);
		QCOMPARE(metaObject->propertyOffset(), 12);
	}
};

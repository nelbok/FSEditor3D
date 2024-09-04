#pragma once

#include <fsd/data/Link.hpp>
#include <fsd/data/Model.hpp>
#include <fsd/data/Object.hpp>
#include <fsd/data/Place.hpp>
#include <fsd/data/Project.hpp>

struct Dummy {
	static void build(fsd::Project& project) {
		[[maybe_unused]] auto* m1 = createModel(project, "Model 1", fsd::Model::ModelType::Place);
		[[maybe_unused]] auto* m2 = createModel(project, "Model 2", fsd::Model::ModelType::Object);
		[[maybe_unused]] auto* m3 = createModel(project, "Model 3", fsd::Model::ModelType::Link);

		[[maybe_unused]] auto* p1 = createPlace(project, "Place 1", m1);
		[[maybe_unused]] auto* p2 = createPlace(project, "Place 2", m1);
		[[maybe_unused]] auto* p3 = createPlace(project, "Place 3", m1);

		[[maybe_unused]] auto* o1 = createObject(project, "Object 1", m2, p2);
		[[maybe_unused]] auto* o2 = createObject(project, "Object 2", m2, p3);

		[[maybe_unused]] auto* l1 = createLink(project, "Link 1", m3, p2);
		[[maybe_unused]] auto* l2 = createLink(project, "Link 2", m3, p3);
		l1->setLink(l2);
		l2->setLink(l1);

		project.setLocalPosition({ 10, 10, 10 });
		project.setLocalRotation({ 10, 10, 10 });
		project.setLocalScale({ 10, 10, 10 });
		project.setDefaultPlace(p1);
	}

private:
	static fsd::Model* createModel(fsd::Project& project, const QString& name, fsd::Model::ModelType type) {
		auto* m = project.createModel();
		m->setName(name);
		m->setModelType(type);
		m->setLocalPosition({ 10, 10, 10 });
		m->setLocalRotation({ 10, 10, 10 });
		m->setLocalScale({ 10, 10, 10 });
		return m;
	}

	static fsd::Place* createPlace(fsd::Project& project, const QString& name, fsd::Model* m) {
		auto* p = project.createPlace();
		p->setName(name);
		p->setModel(m);
		p->setLocalPosition({ 10, 10, 10 });
		p->setLocalRotation({ 10, 10, 10 });
		p->setLocalScale({ 10, 10, 10 });
		return p;
	}

	static fsd::Object* createObject(fsd::Project& project, const QString& name, fsd::Model* m, fsd::Place* p) {
		auto* o = project.createObject();
		o->setName(name);
		o->setModel(m);
		o->setPlace(p);
		o->setLocalPosition({ 10, 10, 10 });
		o->setLocalRotation({ 10, 10, 10 });
		o->setLocalScale({ 10, 10, 10 });
		return o;
	}

	static fsd::Link* createLink(fsd::Project& project, const QString& name, fsd::Model* m, fsd::Place* p) {
		auto* l = project.createLink();
		l->setName(name);
		l->setModel(m);
		l->setPlace(p);
		l->setLocalPosition({ 10, 10, 10 });
		l->setLocalRotation({ 10, 10, 10 });
		l->setLocalScale({ 10, 10, 10 });
		return l;
	}
};

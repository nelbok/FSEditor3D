/*
 * Copyright (c) 2024 Foxxy Soft.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution
 */

#pragma once

#include <QtCore/QList>

#include <fsd/data/Geometry.hpp>

namespace fsd {
class Link;
class Model;
class Object;
class Place;

/**
 * @brief Start class for a project.
 *
 * After creating an instance of Project, calls reset() function.\n
 * Use create, remove, duplicate methods to manage Link, Model, Object, and Place.\n
 * Use save(), load() to manage the file serialization, the format file is Json.
 */
class Project final : public Geometry {
	Q_OBJECT
	/**
	 * @brief The first place the user will see when loading the project.
	 */
	Q_PROPERTY(Place* defaultPlace READ defaultPlace WRITE setDefaultPlace NOTIFY defaultPlaceUpdated)
	/**
	 * @brief List of all entities. Link, Model, Object, and Place.
	 */
	Q_PROPERTY(QList<Entity*> entities READ entities NOTIFY entitiesUpdated)
	/**
	 * @brief List of all links.
	 */
	Q_PROPERTY(QList<Link*> links READ links WRITE setLinks NOTIFY linksUpdated)
	/**
	 * @brief List of all Models.
	 */
	Q_PROPERTY(QList<Model*> models READ models WRITE setModels NOTIFY modelsUpdated)
	/**
	 * @brief List of all Objects.
	 */
	Q_PROPERTY(QList<Object*> objects READ objects WRITE setObjects NOTIFY objectsUpdated)
	/**
	 * @brief List of all Places.
	 */
	Q_PROPERTY(QList<Place*> places READ places WRITE setPlaces NOTIFY placesUpdated)

public:
	Project(QObject* parent = nullptr);
	virtual ~Project();

	virtual void reset() override;

	Place* defaultPlace() const;
	void setDefaultPlace(Place* defaultPlace);

	const QList<Entity*>& entities() const;

	// Links
	const QList<Link*>& links() const;
	void setLinks(const QList<Link*>& link);
	Link* createLink();
	void removeLink(Link* link);
	Link* duplicateLink(Link* link);
	void cleanLinks();

	// Models
	const QList<Model*>& models() const;
	void setModels(const QList<Model*>& models);
	Model* createModel();
	void removeModel(Model* model);
	Model* duplicateModel(Model* model);
	void cleanModels();

	// Objects
	const QList<Object*>& objects() const;
	void setObjects(const QList<Object*>& object);
	Object* createObject();
	void removeObject(Object* object);
	Object* duplicateObject(Object* object);
	void cleanObjects();

	// Places
	const QList<Place*>& places() const;
	void setPlaces(const QList<Place*>& places);
	Place* createPlace();
	void removePlace(Place* place);
	Place* duplicatePlace(Place* place);
	void cleanPlaces();

	virtual Type type() const override;

	virtual void load(const QJsonObject& json) override;
	virtual void save(QJsonObject& json) const override;

private:
	using Entity::copy;

	void addEntity(Entity* entity);
	void removeEntity(Entity* entity);
	void rebuildEntities();

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void defaultPlaceUpdated();
	void entitiesUpdated();
	void linksUpdated();
	void modelsUpdated();
	void objectsUpdated();
	void placesUpdated();
};
} // namespace fsd

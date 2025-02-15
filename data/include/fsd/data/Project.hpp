/*
 * Copyright (c) 2024 Foxxy Soft.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution
 */

#pragma once

#include <fsd/data/FSDataExport.h>

#include <QtCore/QList>

#include <fsd/data/Geometry.hpp>

namespace fsd {
class Link;
class Model;
class Object;
class Place;

template<class TType>
class Container;

/**
 * @brief Start class for a project.
 *
 * After creating an instance of Project, calls reset() function.\n
 * Use create, remove, duplicate methods to manage Link, Model, Object, and Place.\n
 * Use save(), load() to manage the file serialization, the format file is Json.
 */
class FSDATA_EXPORT Project final : public Geometry {
	Q_OBJECT
	/**
	 * @brief The first place the user will see when loading the project.
	 */
	Q_PROPERTY(Place* defaultPlace READ defaultPlace WRITE setDefaultPlace NOTIFY defaultPlaceUpdated)
	/**
	 * @brief The height of the character.
	 */
	Q_PROPERTY(unsigned short height READ height WRITE setHeight NOTIFY heightUpdated)
	/**
	 * @brief List of all entities. Link, Model, Object, and Place.
	 */
	Q_PROPERTY(QList<Entity*> entities READ entities NOTIFY entitiesUpdated)
	/**
	 * @brief List of all links.
	 */
	Q_PROPERTY(Container<Link>* links READ links NOTIFY linksUpdated)
	/**
	 * @brief List of all Models.
	 */
	Q_PROPERTY(Container<Model>* models READ models NOTIFY modelsUpdated)
	/**
	 * @brief List of all Objects.
	 */
	Q_PROPERTY(Container<Object>* objects READ objects NOTIFY objectsUpdated)
	/**
	 * @brief List of all Places.
	 */
	Q_PROPERTY(Container<Place>* places READ places NOTIFY placesUpdated)

public:
	explicit Project(QObject* parent = nullptr);
	~Project() override;

	void reset() override;

	Place* defaultPlace() const;
	void setDefaultPlace(Place* defaultPlace);

	unsigned short height() const;
	void setHeight(unsigned short height);

	QList<Entity*> entities() const;
	Container<Link>* links() const;
	Container<Model>* models() const;
	Container<Object>* objects() const;
	Container<Place>* places() const;

	Type type() const override;

	void load(const QJsonObject& json) override;
	void save(QJsonObject& json) const override;

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
	void heightUpdated();
	void entitiesUpdated();
	void linksUpdated();
	void modelsUpdated();
	void objectsUpdated();
	void placesUpdated();
};
} // namespace fsd

Q_DECLARE_OPAQUE_POINTER(fsd::Container<fsd::Link>*)
Q_DECLARE_OPAQUE_POINTER(fsd::Container<fsd::Model>*)
Q_DECLARE_OPAQUE_POINTER(fsd::Container<fsd::Object>*)
Q_DECLARE_OPAQUE_POINTER(fsd::Container<fsd::Place>*)

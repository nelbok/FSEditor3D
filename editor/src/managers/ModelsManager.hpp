#pragma once

#include <QtCore/QObject>

#include <fsd/data/Project.hpp>

#include "models/LinkModel.hpp"
#include "models/ModelModel.hpp"
#include "models/ObjectModel.hpp"
#include "models/PlaceModel.hpp"

namespace fse {
class ModelsManager : public QObject {
	Q_OBJECT
	Q_PROPERTY(LinkModel* linkModel READ linkModel CONSTANT)
	Q_PROPERTY(ModelModel* modelModel READ modelModel CONSTANT)
	Q_PROPERTY(ObjectModel* objectModel READ objectModel CONSTANT)
	Q_PROPERTY(PlaceModel* placeModel READ placeModel CONSTANT)

	Q_PROPERTY(LinkModel* linkModelWithNone READ linkModelWithNone CONSTANT)
	Q_PROPERTY(ModelModel* modelModelWithNone READ modelModelWithNone CONSTANT)
	Q_PROPERTY(ObjectModel* objectModelWithNone READ objectModelWithNone CONSTANT)
	Q_PROPERTY(PlaceModel* placeModelWithNone READ placeModelWithNone CONSTANT)

public:
	ModelsManager(QObject* parent = nullptr);
	virtual ~ModelsManager();

	void init(fsd::Project* project);

	LinkModel* linkModel() const;
	ModelModel* modelModel() const;
	ObjectModel* objectModel() const;
	PlaceModel* placeModel() const;

	LinkModel* linkModelWithNone() const;
	ModelModel* modelModelWithNone() const;
	ObjectModel* objectModelWithNone() const;
	PlaceModel* placeModelWithNone() const;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;
};
} // namespace fse

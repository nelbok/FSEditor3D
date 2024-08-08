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

public:
	ModelsManager(QObject* parent = nullptr);
	virtual ~ModelsManager();

	void init(fsd::Project* project);

	LinkModel* linkModel() const;
	ModelModel* modelModel() const;
	ObjectModel* objectModel() const;
	PlaceModel* placeModel() const;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;
};
} // namespace fse

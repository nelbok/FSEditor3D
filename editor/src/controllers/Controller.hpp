#pragma once

#include <QtCore/QObject>

#include <lh/data/Project.hpp>

#include "models/PlaceModel.hpp"
#include "About.hpp"

namespace lhe {
class Controller : public QObject {
	Q_OBJECT
	Q_PROPERTY(About* about READ about CONSTANT)
	Q_PROPERTY(lh::Project* project READ project CONSTANT)
	Q_PROPERTY(PlaceModel* placeModel READ placeModel CONSTANT)

public:
	Controller(QObject* parent = nullptr);
	virtual ~Controller();

	void init();

	About* about() const;
	lh::Project* project() const;
	PlaceModel* placeModel() const;

private:
	About* _about{ nullptr };
	lh::Project* _project{ nullptr };
	PlaceModel* _placeModel{ nullptr };
};
} // namespace lhe

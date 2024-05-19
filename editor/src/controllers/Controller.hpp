#pragma once

#include <QtCore/QObject>

#include <lh/data/Project.hpp>

#include "commands/CharacterCommand.hpp"
#include "commands/EntityCommand.hpp"
#include "commands/LinkCommand.hpp"
#include "commands/ModelCommand.hpp"
#include "commands/PlaceCommand.hpp"
#include "commands/PlacementCommand.hpp"
#include "commands/ProjectCommand.hpp"

#include "models/CharacterModel.hpp"
#include "models/LinkModel.hpp"
#include "models/ModelModel.hpp"
#include "models/PlaceModel.hpp"

#include "About.hpp"
#include "Commands.hpp"

namespace lhe {
class Controller : public QObject {
	Q_OBJECT
	Q_PROPERTY(About* about READ about CONSTANT)
	Q_PROPERTY(Commands* commands READ commands CONSTANT)
	Q_PROPERTY(lh::Project* project READ project CONSTANT)

	// commands
	Q_PROPERTY(CharacterCommand* characterCommand READ characterCommand CONSTANT)
	Q_PROPERTY(EntityCommand* entityCommand READ entityCommand CONSTANT)
	Q_PROPERTY(LinkCommand* linkCommand READ linkCommand CONSTANT)
	Q_PROPERTY(ModelCommand* modelCommand READ modelCommand CONSTANT)
	Q_PROPERTY(PlaceCommand* placeCommand READ placeCommand CONSTANT)
	Q_PROPERTY(PlacementCommand* placementCommand READ placementCommand CONSTANT)
	Q_PROPERTY(ProjectCommand* projectCommand READ projectCommand CONSTANT)

	// models
	Q_PROPERTY(CharacterModel* characterModel READ characterModel CONSTANT)
	Q_PROPERTY(LinkModel* linkModel READ linkModel CONSTANT)
	Q_PROPERTY(ModelModel* modelModel READ modelModel CONSTANT)
	Q_PROPERTY(PlaceModel* placeModel READ placeModel CONSTANT)

public:
	Controller(QObject* parent = nullptr);
	virtual ~Controller();

	void init();

	Q_INVOKABLE void reset();
	Q_INVOKABLE void load(const QUrl& url);
	Q_INVOKABLE void save(const QUrl& url);

	About* about() const;
	Commands* commands() const;
	lh::Project* project() const;

	// commands
	CharacterCommand* characterCommand() const;
	EntityCommand* entityCommand() const;
	LinkCommand* linkCommand() const;
	ModelCommand* modelCommand() const;
	PlaceCommand* placeCommand() const;
	PlacementCommand* placementCommand() const;
	ProjectCommand* projectCommand() const;

	// models
	CharacterModel* characterModel() const;
	LinkModel* linkModel() const;
	ModelModel* modelModel() const;
	PlaceModel* placeModel() const;

private:
	About* _about{ nullptr };
	Commands* _commands{ nullptr };
	lh::Project* _project{ nullptr };

	// commands
	CharacterCommand* _characterCommand{ nullptr };
	EntityCommand* _entityCommand{ nullptr };
	LinkCommand* _linkCommand{ nullptr };
	ModelCommand* _modelCommand{ nullptr };
	PlaceCommand* _placeCommand{ nullptr };
	PlacementCommand* _placementCommand{ nullptr };
	ProjectCommand* _projectCommand{ nullptr };

	// models
	CharacterModel* _characterModel{ nullptr };
	LinkModel* _linkModel{ nullptr };
	ModelModel* _modelModel{ nullptr };
	PlaceModel* _placeModel{ nullptr };
};
} // namespace lhe

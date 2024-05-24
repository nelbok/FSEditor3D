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

namespace lhe {
class CommandsManager : public QObject {
	Q_OBJECT

	Q_PROPERTY(bool canUndo READ canUndo NOTIFY updated)
	Q_PROPERTY(bool canRedo READ canRedo NOTIFY updated)

	Q_PROPERTY(CharacterCommand* characterCommand READ characterCommand CONSTANT)
	Q_PROPERTY(EntityCommand* entityCommand READ entityCommand CONSTANT)
	Q_PROPERTY(LinkCommand* linkCommand READ linkCommand CONSTANT)
	Q_PROPERTY(ModelCommand* modelCommand READ modelCommand CONSTANT)
	Q_PROPERTY(PlaceCommand* placeCommand READ placeCommand CONSTANT)
	Q_PROPERTY(PlacementCommand* placementCommand READ placementCommand CONSTANT)
	Q_PROPERTY(ProjectCommand* projectCommand READ projectCommand CONSTANT)

public:
	CommandsManager(QObject* parent = nullptr);
	virtual ~CommandsManager();

	void init(lh::Project* project);
	void reset();

	bool canUndo()const;
	bool canRedo()const;
	Q_INVOKABLE void undo();
	Q_INVOKABLE void redo();

	CharacterCommand* characterCommand() const;
	EntityCommand* entityCommand() const;
	LinkCommand* linkCommand() const;
	ModelCommand* modelCommand() const;
	PlaceCommand* placeCommand() const;
	PlacementCommand* placementCommand() const;
	ProjectCommand* projectCommand() const;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void updated();
};
} // namespace lhe

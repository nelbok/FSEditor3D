#pragma once

#include <QtCore/QObject>

#include <fsd/data/Project.hpp>

#include "commands/EntityCommand.hpp"
#include "commands/GeometryCommand.hpp"
#include "commands/LinkCommand.hpp"
#include "commands/ModelCommand.hpp"
#include "commands/ObjectCommand.hpp"
#include "commands/PlaceCommand.hpp"
#include "commands/PlacementCommand.hpp"
#include "commands/ProjectCommand.hpp"
#include "commands/ShapeCommand.hpp"

namespace fse {
class CommandsManager : public QObject {
	Q_OBJECT

	Q_PROPERTY(bool canUndo READ canUndo NOTIFY updated)
	Q_PROPERTY(bool canRedo READ canRedo NOTIFY updated)
	Q_PROPERTY(bool isModified READ isModified WRITE setIsModified NOTIFY updated)

	Q_PROPERTY(EntityCommand* entityCommand READ entityCommand CONSTANT)
	Q_PROPERTY(GeometryCommand* geometryCommand READ geometryCommand CONSTANT)
	Q_PROPERTY(LinkCommand* linkCommand READ linkCommand CONSTANT)
	Q_PROPERTY(ModelCommand* modelCommand READ modelCommand CONSTANT)
	Q_PROPERTY(ObjectCommand* objectCommand READ objectCommand CONSTANT)
	Q_PROPERTY(PlaceCommand* placeCommand READ placeCommand CONSTANT)
	Q_PROPERTY(PlacementCommand* placementCommand READ placementCommand CONSTANT)
	Q_PROPERTY(ProjectCommand* projectCommand READ projectCommand CONSTANT)
	Q_PROPERTY(ShapeCommand* shapeCommand READ shapeCommand CONSTANT)

public:
	CommandsManager(QObject* parent = nullptr);
	virtual ~CommandsManager();

	void init(fsd::Project* project);
	void reset();

	bool canUndo()const;
	bool canRedo()const;
	Q_INVOKABLE void undo();
	Q_INVOKABLE void redo();

	bool isModified() const;
	void setIsModified(bool isModified);

	EntityCommand* entityCommand() const;
	GeometryCommand* geometryCommand() const;
	LinkCommand* linkCommand() const;
	ModelCommand* modelCommand() const;
	ObjectCommand* objectCommand() const;
	PlaceCommand* placeCommand() const;
	PlacementCommand* placementCommand() const;
	ProjectCommand* projectCommand() const;
	ShapeCommand* shapeCommand() const;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void updated();
};
} // namespace fse

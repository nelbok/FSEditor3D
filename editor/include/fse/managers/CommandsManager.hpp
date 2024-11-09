#pragma once

#include <QtCore/QObject>

#include <fsd/data/Project.hpp>

#include <fse/commands/EntityCommand.hpp>
#include <fse/commands/GeometryCommand.hpp>
#include <fse/commands/LinkCommand.hpp>
#include <fse/commands/ModelCommand.hpp>
#include <fse/commands/ObjectCommand.hpp>
#include <fse/commands/PlaceCommand.hpp>
#include <fse/commands/PlacementCommand.hpp>
#include <fse/commands/ProjectCommand.hpp>
#include <fse/commands/ShapeCommand.hpp>

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
	explicit CommandsManager(QObject* parent = nullptr);
	~CommandsManager() override;

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

#pragma once

#include <QtCore/QObject>

#include <fsd/data/Project.hpp>

namespace fse {
class CommandsManager;
class Commands;

class ProjectCommand : public QObject {
	Q_OBJECT

public:
	explicit ProjectCommand(fsd::Project* project, CommandsManager* manager, Commands* commands);
	~ProjectCommand() override;

	Q_INVOKABLE void setDefaultPlace(fsd::Place* defaultPlace);

	Q_INVOKABLE void createLink();
	Q_INVOKABLE void removeLink(fsd::Link* link);
	Q_INVOKABLE void duplicateLink(fsd::Link* link);

	Q_INVOKABLE void createModel();
	Q_INVOKABLE void removeModel(fsd::Model* model);
	Q_INVOKABLE void duplicateModel(fsd::Model* model);

	Q_INVOKABLE void createObject();
	Q_INVOKABLE void removeObject(fsd::Object* object);
	Q_INVOKABLE void duplicateObject(fsd::Object* object);

	Q_INVOKABLE void createPlace();
	Q_INVOKABLE void removePlace(fsd::Place* place);
	Q_INVOKABLE void duplicatePlace(fsd::Place* place);

private:
	fsd::Project* _p{ nullptr };
	CommandsManager* _mng{ nullptr };
	Commands* _cmd{ nullptr };
};
} // namespace fse

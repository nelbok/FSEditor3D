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

	Q_INVOKABLE fsd::EntryPoint* createEntryPoint();
	Q_INVOKABLE void removeEntryPoint(fsd::EntryPoint* entryPoint);
	Q_INVOKABLE fsd::EntryPoint* duplicateEntryPoint(fsd::EntryPoint* entryPoint);

	Q_INVOKABLE fsd::Link* createLink();
	Q_INVOKABLE void removeLink(fsd::Link* link);
	Q_INVOKABLE fsd::Link* duplicateLink(fsd::Link* link);

	Q_INVOKABLE fsd::Model* createModel();
	Q_INVOKABLE void removeModel(fsd::Model* model);
	Q_INVOKABLE fsd::Model* duplicateModel(fsd::Model* model);

	Q_INVOKABLE fsd::Object* createObject();
	Q_INVOKABLE void removeObject(fsd::Object* object);
	Q_INVOKABLE fsd::Object* duplicateObject(fsd::Object* object);

	Q_INVOKABLE fsd::Place* createPlace();
	Q_INVOKABLE void removePlace(fsd::Place* place);
	Q_INVOKABLE fsd::Place* duplicatePlace(fsd::Place* place);

private:
	fsd::Project* _p{ nullptr };
	CommandsManager* _mng{ nullptr };
	Commands* _cmd{ nullptr };
};
} // namespace fse

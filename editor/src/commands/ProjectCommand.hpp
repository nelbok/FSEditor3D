#pragma once

#include <QtCore/QObject>

#include <fsd/data/Project.hpp>

namespace fse {
class CommandsManager;
class Commands;

class ProjectCommand : public QObject {
	Q_OBJECT

public:
	ProjectCommand(fsd::Project* project, CommandsManager* mng, Commands* commands);
	virtual ~ProjectCommand();

	Q_INVOKABLE void setDefaultPlace(fsd::Place* defaultPlace);

	Q_INVOKABLE void createCharacter();
	Q_INVOKABLE void removeCharacter(fsd::Character* character);
	Q_INVOKABLE void duplicateCharacter(fsd::Character* character);

	Q_INVOKABLE void createLink();
	Q_INVOKABLE void removeLink(fsd::Link* link);
	Q_INVOKABLE void duplicateLink(fsd::Link* link);

	Q_INVOKABLE void createModel();
	Q_INVOKABLE void removeModel(fsd::Model* model);
	Q_INVOKABLE void duplicateModel(fsd::Model* model);

	Q_INVOKABLE void createPlace();
	Q_INVOKABLE void removePlace(fsd::Place* place);
	Q_INVOKABLE void duplicatePlace(fsd::Place* place);

protected:
	fsd::Project* _p{ nullptr };
	CommandsManager* _cm{ nullptr };
	Commands* _c{ nullptr };
};
} // namespace fse

#pragma once

#include <QtCore/QObject>

#include <lh/data/Project.hpp>

namespace lhe {
class CommandsManager;
class Commands;

class ProjectCommand : public QObject {
	Q_OBJECT

public:
	ProjectCommand(lh::Project* project, CommandsManager* mng, Commands* commands);
	virtual ~ProjectCommand();

	Q_INVOKABLE void setDefaultPlace(lh::Place* defaultPlace);

	Q_INVOKABLE void createCharacter();
	Q_INVOKABLE void removeCharacter(lh::Character* character);
	Q_INVOKABLE void duplicateCharacter(lh::Character* character);

	Q_INVOKABLE void createLink();
	Q_INVOKABLE void removeLink(lh::Link* link);
	Q_INVOKABLE void duplicateLink(lh::Link* link);

	Q_INVOKABLE void createModel();
	Q_INVOKABLE void removeModel(lh::Model* model);
	Q_INVOKABLE void duplicateModel(lh::Model* model);

	Q_INVOKABLE void createPlace();
	Q_INVOKABLE void removePlace(lh::Place* place);
	Q_INVOKABLE void duplicatePlace(lh::Place* place);

protected:
	lh::Project* _p{ nullptr };
	CommandsManager* _cm{ nullptr };
	Commands* _c{ nullptr };
};
} // namespace lhe

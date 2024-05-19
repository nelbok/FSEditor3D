#pragma once

#include <QtCore/QObject>

#include <lh/data/Project.hpp>

namespace lhe {
class Commands;
class Controller;

class ProjectCommand : public QObject {
	Q_OBJECT

public:
	ProjectCommand(Controller* controller);
	virtual ~ProjectCommand();

	Q_INVOKABLE void setDefaultPlace(lh::Place* defaultPlace);

	Q_INVOKABLE void createCharacter();
	Q_INVOKABLE void removeCharacter(lh::Character* character);
	Q_INVOKABLE void duplicateCharacter(lh::Character* character);

	Q_INVOKABLE void createLink();
	Q_INVOKABLE void removeLink(lh::Link* link);
	Q_INVOKABLE void duplicateLink(lh::Link* link);

	Q_INVOKABLE void createPlace();
	Q_INVOKABLE void removePlace(lh::Place* place);
	Q_INVOKABLE void duplicatePlace(lh::Place* place);

protected:
	Controller* _c{ nullptr };
	Commands* _cm{ nullptr };
	lh::Project* _p{ nullptr };
};
} // namespace lhe

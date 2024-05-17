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

	Q_INVOKABLE	void setDefaultPlace(lh::Place* defaultPlace);

protected:
	Commands* _c{ nullptr };
	lh::Project* _p{ nullptr };
};
} // namespace lhe

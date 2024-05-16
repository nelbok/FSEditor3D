#pragma once

#include <QtCore/QObject>

#include <lh/data/Project.hpp>

namespace lhe {
class Commands;

class ProjectCommand : public QObject {
	Q_OBJECT

public:
	ProjectCommand(Commands* commands);
	virtual ~ProjectCommand();

protected:
	Commands* _c{ nullptr };
};
} // namespace lhe

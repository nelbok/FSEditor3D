#pragma once

#include <QtCore/QObject>

#include <lh/data/Model.hpp>

namespace lhe {
class Commands;

class ModelCommand : public QObject {
	Q_OBJECT

public:
	ModelCommand(Commands* commands);
	virtual ~ModelCommand();

protected:
	Commands* _c{ nullptr };
};
} // namespace lhe

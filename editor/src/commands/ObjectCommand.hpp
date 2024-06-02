#pragma once

#include <QtCore/QObject>

#include <lh/data/Object.hpp>

namespace lhe {
class Commands;

class ObjectCommand : public QObject {
	Q_OBJECT

public:
	ObjectCommand(Commands* commands);
	virtual ~ObjectCommand();

	Q_INVOKABLE void setModel(lh::Object* object, lh::Model* model);

protected:
	Commands* _c{ nullptr };
};
} // namespace lhe

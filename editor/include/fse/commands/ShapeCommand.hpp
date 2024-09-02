#pragma once

#include <QtCore/QObject>

#include <fsd/data/Shape.hpp>

namespace fse {
class Commands;

class ShapeCommand : public QObject {
	Q_OBJECT

public:
	ShapeCommand(Commands* commands);
	virtual ~ShapeCommand();

	Q_INVOKABLE void setModel(fsd::Shape* shape, fsd::Model* model);

protected:
	Commands* _c{ nullptr };
};
} // namespace fse

#pragma once

#include <QtCore/QObject>

#include <fsd/data/Shape.hpp>

namespace fse {
class Commands;

class ShapeCommand : public QObject {
	Q_OBJECT

public:
	explicit ShapeCommand(Commands* commands);
	~ShapeCommand() override;

	Q_INVOKABLE void setModel(fsd::Shape* shape, fsd::Model* model);

private:
	Commands* _cmd{ nullptr };
};
} // namespace fse

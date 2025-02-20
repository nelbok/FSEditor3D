#pragma once

#include <QtCore/QObject>

#include <fsd/data/EntryPoint.hpp>

namespace fse {
class Commands;
class PreviewManager;

class EntryPointCommand : public QObject {
	Q_OBJECT

public:
	explicit EntryPointCommand(Commands* commands);
	~EntryPointCommand() override;

	Q_INVOKABLE void setPosition(fsd::EntryPoint* entryPoint, const QVector3D& position);
	Q_INVOKABLE void setRotation(fsd::EntryPoint* entryPoint, double rotation);
	Q_INVOKABLE void setPlace(fsd::EntryPoint* entryPoint, fsd::Place* place);
	Q_INVOKABLE void assignCameraCoordinates(fsd::EntryPoint* entryPoint, fse::PreviewManager* mng);

private:
	Commands* _cmd{ nullptr };
};
} // namespace fse

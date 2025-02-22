#pragma once

#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtGui/QVector3D>

#include <fsd/data/EntryPoint.hpp>
#include <fsd/data/Place.hpp>

namespace fse {
class Manager;

struct PreviewData {
	Q_GADGET
	Q_PROPERTY(fsd::Geometry* geometry MEMBER geometry CONSTANT)
	Q_PROPERTY(QUrl basePath MEMBER basePath CONSTANT)
	Q_PROPERTY(QUrl model MEMBER model CONSTANT)
	Q_PROPERTY(QVector3D offset MEMBER offset CONSTANT)
public:
	fsd::Geometry* geometry{ nullptr };
	QUrl basePath;
	QUrl model;
	QVector3D offset{ 0, 0, 0 };
};

struct EntryPointData {
	Q_GADGET
	Q_PROPERTY(fsd::EntryPoint* entryPoint MEMBER entryPoint CONSTANT)
	Q_PROPERTY(QVector3D offset MEMBER offset CONSTANT)
public:
	fsd::EntryPoint* entryPoint{ nullptr };
	QVector3D offset{ 0, 0, 0 };
};

class PreviewManager : public QObject {
	Q_OBJECT
	Q_PROPERTY(unsigned height READ height WRITE setHeight NOTIFY heightUpdated)
	Q_PROPERTY(QVector3D cameraPosition READ cameraPosition WRITE setCameraPosition NOTIFY cameraPositionUpdated)
	Q_PROPERTY(QVector3D cameraRotation READ cameraRotation WRITE setCameraRotation NOTIFY cameraRotationUpdated)

	Q_PROPERTY(bool areEntryPointsVisible READ areEntryPointsVisible WRITE setAreEntryPointsVisible NOTIFY areEntryPointsVisibleUpdated)
	Q_PROPERTY(bool areLinksVisible READ areLinksVisible WRITE setAreLinksVisible NOTIFY areLinksVisibleUpdated)
	Q_PROPERTY(bool areObjectsVisible READ areObjectsVisible WRITE setAreObjectsVisible NOTIFY areObjectsVisibleUpdated)
	Q_PROPERTY(bool isWorldMode READ isWorldMode WRITE setWorldMode NOTIFY isWorldModeUpdated)
	Q_PROPERTY(bool isDebugMode READ isDebugMode WRITE setDebugMode NOTIFY isDebugModeUpdated)
	Q_PROPERTY(ViewMode viewMode READ viewMode WRITE setViewMode NOTIFY viewModeUpdated)
	Q_PROPERTY(bool isGravityEnabled READ isGravityEnabled WRITE setGravityEnabled NOTIFY gravityEnabledUpdated)

	Q_PROPERTY(QList<PreviewData> datas READ datas NOTIFY previewUpdated)
	Q_PROPERTY(QList<EntryPointData> entryPointDatas READ entryPointDatas NOTIFY previewUpdated)

public:
	enum class ViewMode {
		Design,
		Collide,
	};
	Q_ENUM(ViewMode)

	explicit PreviewManager(QObject* parent = nullptr);
	~PreviewManager() override;

	void init(Manager* manager);
	void reset();

	unsigned height() const;
	void setHeight(unsigned height);

	const QVector3D& cameraPosition() const;
	void setCameraPosition(const QVector3D& cameraPosition);

	const QVector3D& cameraRotation() const;
	void setCameraRotation(const QVector3D& cameraRotation);

	bool areEntryPointsVisible() const;
	void setAreEntryPointsVisible(bool visible);

	bool areLinksVisible() const;
	void setAreLinksVisible(bool visible);

	bool areObjectsVisible() const;
	void setAreObjectsVisible(bool visible);

	bool isWorldMode() const;
	void setWorldMode(bool enabled);

	bool isDebugMode() const;
	void setDebugMode(bool enabled);

	ViewMode viewMode() const;
	void setViewMode(ViewMode viewMode);

	bool isGravityEnabled() const;
	void setGravityEnabled(bool enabled);

	Q_INVOKABLE void teleportOn(const fsd::EntryPoint* entryPoint);
	Q_INVOKABLE void centerOnCurrent();
	Q_INVOKABLE void switchEntryPointsVisible();
	Q_INVOKABLE void switchLinksVisible();
	Q_INVOKABLE void switchObjectsVisible();
	Q_INVOKABLE void switchWorldMode();
	Q_INVOKABLE void switchDebugMode();
	Q_INVOKABLE void switchViewMode();
	Q_INVOKABLE void switchGravity();

	QList<PreviewData> datas() const;
	QList<EntryPointData> entryPointDatas() const;

private:
	void fullMapDatas(QList<fsd::Entity*>& parsed, fsd::Place* place, const QVector3D& offset = { 0, 0, 0 }) const;
	void fillDatas(QList<fsd::Entity*>& parsed, fsd::Entity* geometry, const QVector3D& offset = { 0, 0, 0 }) const;

	struct Impl;
	std::unique_ptr<Impl> _impl;

private slots:
	void updateDatas();
	void updateConnections();

signals:
	void heightUpdated();
	void teleported();
	void cameraPositionUpdated();
	void cameraRotationUpdated();
	void previewUpdated();

	void areEntryPointsVisibleUpdated();
	void areLinksVisibleUpdated();
	void areObjectsVisibleUpdated();
	void isWorldModeUpdated();
	void isDebugModeUpdated();
	void viewModeUpdated();
	void gravityEnabledUpdated();
};
} // namespace fse

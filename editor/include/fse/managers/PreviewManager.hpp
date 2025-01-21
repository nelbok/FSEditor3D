#pragma once

#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtGui/QVector3D>

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

class PreviewManager : public QObject {
	Q_OBJECT
	Q_PROPERTY(QVector3D cameraPosition READ cameraPosition WRITE setCameraPosition NOTIFY cameraPositionUpdated)
	Q_PROPERTY(QVector3D cameraRotation READ cameraRotation WRITE setCameraRotation NOTIFY cameraRotationUpdated)

	Q_PROPERTY(bool areOtherDatasVisible READ areOtherDatasVisible WRITE setAreOtherDatasVisible NOTIFY areOtherDatasVisibleUpdated)
	Q_PROPERTY(bool areOriginsVisible READ areOriginsVisible WRITE setAreOriginsVisible NOTIFY areOriginsVisibleUpdated)
	Q_PROPERTY(bool isWorldMode READ isWorldMode WRITE setWorldMode NOTIFY isWorldModeUpdated)
	Q_PROPERTY(bool isDebugMode READ isDebugMode WRITE setDebugMode NOTIFY isDebugModeUpdated)
	Q_PROPERTY(ViewMode viewMode READ viewMode WRITE setViewMode NOTIFY viewModeUpdated)
	Q_PROPERTY(bool isGravityEnabled READ isGravityEnabled WRITE setGravityEnabled NOTIFY gravityEnabledUpdated)

	Q_PROPERTY(QList<PreviewData> datas READ datas NOTIFY previewUpdated)

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

	const QVector3D& cameraPosition() const;
	void setCameraPosition(const QVector3D& cameraPosition);

	const QVector3D& cameraRotation() const;
	void setCameraRotation(const QVector3D& cameraRotation);

	bool areOtherDatasVisible() const;
	void setAreOtherDatasVisible(bool visible);

	bool areOriginsVisible() const;
	void setAreOriginsVisible(bool visible);

	bool isWorldMode() const;
	void setWorldMode(bool enabled);

	bool isDebugMode() const;
	void setDebugMode(bool enabled);

	ViewMode viewMode() const;
	void setViewMode(ViewMode viewMode);

	bool isGravityEnabled() const;
	void setGravityEnabled(bool enabled);

	Q_INVOKABLE void centerOnCurrent();
	Q_INVOKABLE void switchOtherDatasVisible();
	Q_INVOKABLE void switchOriginsVisible();
	Q_INVOKABLE void switchWorldMode();
	Q_INVOKABLE void switchDebugMode();
	Q_INVOKABLE void switchViewMode();
	Q_INVOKABLE void switchGravity();

	QList<PreviewData> datas() const;

private:
	void fullMapDatas(QList<PreviewData>& datas, QList<fsd::Geometry*>& parsed, fsd::Place* place, const QVector3D& offset = { 0, 0, 0 }) const;

	void fillDatas(QList<PreviewData>& datas, QList<fsd::Geometry*>& parsed, fsd::Geometry* geometry, bool useRefs) const;
	void fillDatas(QList<PreviewData>& datas, QList<fsd::Geometry*>& parsed, fsd::Geometry* geometry, const QVector3D& offset = { 0, 0, 0 }, bool useRefs = false) const;

	struct Impl;
	std::unique_ptr<Impl> _impl;

private slots:
	void updateConnections();

signals:
	void cameraPositionUpdated();
	void cameraRotationUpdated();
	void previewUpdated();

	void areOtherDatasVisibleUpdated();
	void areOriginsVisibleUpdated();
	void isWorldModeUpdated();
	void isDebugModeUpdated();
	void viewModeUpdated();
	void gravityEnabledUpdated();
};
} // namespace fse

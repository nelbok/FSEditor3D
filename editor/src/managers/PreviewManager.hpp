#pragma once

#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtGui/QVector3D>

#include <fsd/data/Geometry.hpp>

namespace fse {
class Manager;

struct PreviewData {
	Q_GADGET
	Q_PROPERTY(fsd::Geometry* geometry MEMBER geometry CONSTANT)
	Q_PROPERTY(QUrl model MEMBER model CONSTANT)
public:
	fsd::Geometry* geometry;
	QUrl model;
};

class PreviewManager : public QObject {
	Q_OBJECT
	Q_PROPERTY(QVector3D cameraPosition READ cameraPosition WRITE setCameraPosition NOTIFY cameraPositionUpdated)
	Q_PROPERTY(QVector3D cameraRotation READ cameraRotation WRITE setCameraRotation NOTIFY cameraRotationUpdated)

	Q_PROPERTY(bool areOriginsVisible READ areOriginsVisible NOTIFY areOriginsVisibleUpdated)

	Q_PROPERTY(QList<PreviewData> datas READ datas NOTIFY previewUpdated)

public:
	PreviewManager(QObject* parent = nullptr);
	virtual ~PreviewManager();

	void init(Manager* manager);
	void reset();

	const QVector3D& cameraPosition() const;
	void setCameraPosition(const QVector3D& cameraPosition);

	const QVector3D& cameraRotation() const;
	void setCameraRotation(const QVector3D& cameraRotation);

	bool areOriginsVisible() const;

	Q_INVOKABLE void centerOnCurrent();
	Q_INVOKABLE void switchOriginsVisible();

	QList<PreviewData> datas() const;

private:
	void fillDatas(QList<PreviewData>& datas, fsd::Geometry* geometry, bool useRefs = false) const;

	struct Impl;
	std::unique_ptr<Impl> _impl;

private slots:
	void updateConnections();

signals:
	void cameraPositionUpdated();
	void cameraRotationUpdated();
	void previewUpdated();

	void areOriginsVisibleUpdated();
};
} // namespace fse

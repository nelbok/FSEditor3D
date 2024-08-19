#pragma once

#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QUrl>

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
	Q_PROPERTY(QList<PreviewData> datas READ datas NOTIFY previewUpdated)

public:
	PreviewManager(QObject* parent = nullptr);
	virtual ~PreviewManager();

	void init(Manager* manager);

	QList<PreviewData> datas() const;

private:
	void fillDatas(QList<PreviewData>& datas, fsd::Geometry* geometry) const;

	struct Impl;
	std::unique_ptr<Impl> _impl;

private slots:
	void updateConnections();

signals:
	void previewUpdated();
};
} // namespace fse

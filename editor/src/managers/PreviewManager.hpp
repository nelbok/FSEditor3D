#pragma once

#include <QtCore/QObject>

#include <fsd/data/Project.hpp>
#include <fsd/data/Model.hpp>

namespace fse {
class SelectionManager;
class PreviewManager : public QObject {
	Q_OBJECT

	Q_PROPERTY(fsd::Geometry* mainGeometry READ mainGeometry NOTIFY previewUpdated)
	Q_PROPERTY(fsd::Model* mainModel READ mainModel NOTIFY previewUpdated)

public:
	PreviewManager(QObject* parent = nullptr);
	virtual ~PreviewManager();

	void init(fsd::Project* project, SelectionManager* manager);

	fsd::Geometry* mainGeometry() const;
	fsd::Model* mainModel() const;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

private slots:
	void updateConnections();

signals:
	void previewUpdated();
};
} // namespace fse

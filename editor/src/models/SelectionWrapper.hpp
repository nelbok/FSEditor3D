#pragma once

#include <QtCore/QAbstractItemModel>
#include <QtCore/QObject>
#include <QtCore/QUuid>

#include <fsd/data/Project.hpp>

namespace fse {
class SelectionWrapper : public QObject {
	Q_OBJECT
	Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentUpdated)
	Q_PROPERTY(fsd::Entity* currentData READ currentData WRITE setCurrentData NOTIFY currentUpdated)
	Q_PROPERTY(QAbstractItemModel* model READ model WRITE setModel NOTIFY modelUpdated)
	Q_PROPERTY(fsd::Project* project READ project WRITE setProject NOTIFY projectUpdated)

public:
	SelectionWrapper(QObject* parent = nullptr);
	virtual ~SelectionWrapper();

	int currentIndex() const;
	void setCurrentIndex(int currentIndex);

	fsd::Entity* currentData() const;
	void setCurrentData(fsd::Entity* currentData);

	QAbstractItemModel* model() const;
	void setModel(QAbstractItemModel* model);

	fsd::Project* project() const;
	void setProject(fsd::Project* project);

private:
	int getRole(const QByteArray& name) const;

private:
	fsd::Entity* _currentData{ nullptr };
	QAbstractItemModel* _model{ nullptr };
	fsd::Project* _project{ nullptr };

signals:
	void currentUpdated();
	void modelUpdated();
	void projectUpdated();
};

} // namespace fse

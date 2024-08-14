#pragma once

#include <QtCore/QAbstractItemModel>
#include <QtCore/QObject>

#include <fsd/data/Entity.hpp>

namespace fse {
class SelectionWrapper : public QObject {
	Q_OBJECT
	Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentUpdated)
	Q_PROPERTY(fsd::Entity* currentData READ currentData WRITE setCurrentData NOTIFY currentUpdated)
	Q_PROPERTY(QAbstractItemModel* model READ model WRITE setModel NOTIFY modelUpdated)

public:
	SelectionWrapper(QObject* parent = nullptr);
	virtual ~SelectionWrapper();

	int currentIndex() const;
	void setCurrentIndex(int currentIndex);

	fsd::Entity* currentData() const;
	void setCurrentData(fsd::Entity* currentData);

	QAbstractItemModel* model() const;
	void setModel(QAbstractItemModel* model);

private:
	int getRole(const QByteArray& name) const;

private:
	fsd::Entity* _currentData{ nullptr };
	QAbstractItemModel* _model{ nullptr };

signals:
	void currentUpdated();
	void modelUpdated();
};

} // namespace fse

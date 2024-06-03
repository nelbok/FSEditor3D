#pragma once

#include <QtCore/QAbstractItemModel>
#include <QtCore/QObject>
#include <QtCore/QUuid>

#include <lh/data/Entity.hpp>

namespace lhe {
class SelectionWrapper : public QObject {
	Q_OBJECT
	Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentUpdated)
	Q_PROPERTY(lh::Entity* currentData READ currentData WRITE setCurrentData NOTIFY currentUpdated)
	Q_PROPERTY(QAbstractItemModel* model READ model WRITE setModel NOTIFY modelUpdated)

public:
	SelectionWrapper(QObject* parent = nullptr);
	virtual ~SelectionWrapper();

	int currentIndex() const;
	void setCurrentIndex(int currentIndex);

	lh::Entity* currentData() const;
	void setCurrentData(lh::Entity* currentData);

	QAbstractItemModel* model() const;
	void setModel(QAbstractItemModel* model);

private:
	int getRole(const QByteArray& name) const;

private:
	QUuid _currentUuid{};
	QAbstractItemModel* _model{ nullptr };

signals:
	void currentUpdated();
	void modelUpdated();
};

} // namespace lhe

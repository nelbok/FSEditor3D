#pragma once

#include <QtCore/QAbstractListModel>
#include <QtCore/QUuid>

#include <lh/data/Entity.hpp>

namespace lhe {
class EntityModel : public QAbstractListModel {
	Q_OBJECT
	Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexUpdated)
	Q_PROPERTY(lh::Entity* currentData READ currentData WRITE setCurrentData NOTIFY currentDataUpdated)
	Q_PROPERTY(QList<lh::Entity*> model READ model WRITE setModel NOTIFY modelUpdated)

public:
	EntityModel(QObject* parent = nullptr);
	virtual ~EntityModel();

	int currentIndex() const;
	void setCurrentIndex(int currentIndex);

	lh::Entity* currentData() const;
	void setCurrentData(lh::Entity* currentData);

	const QList<lh::Entity*>& model() const;
	void setModel(const QList<lh::Entity*>& model);

	int rowCount(const QModelIndex& parent = QModelIndex()) const;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

protected:
	QHash<int, QByteArray> roleNames() const;

private slots:
	void sort();

private:
	QUuid _currentUuid{};
	QList<lh::Entity*> _model{};

signals:
	void currentIndexUpdated();
	void currentDataUpdated();
	void modelUpdated();
};

} // namespace lhe

#pragma once

#include <QtCore/QAbstractListModel>

#include <lh/data/Project.hpp>

namespace lhe {
class EntityModel : public QAbstractListModel {
	Q_OBJECT

public:
	EntityModel(QObject* parent = nullptr);
	virtual ~EntityModel();

	virtual void init(lh::Project* project) = 0;
	const QList<lh::Entity*>& datas() const;

	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	virtual QHash<int, QByteArray> roleNames() const override;

protected:
	template<class T>
	void updateDatas(const QList<T*>& datas) {
		// Disconnect
		for (auto* entity : _datas) {
			disconnect(entity, &lh::Entity::nameUpdated, this, &EntityModel::sortDatas);
		}
		_datas.clear();

		// Fill the new model
		for (auto* entity : datas) {
			_datas.append(entity);
			connect(entity, &lh::Entity::nameUpdated, this, &EntityModel::sortDatas);
		}

		// Sort
		sortDatas();
	}

private slots:
	void sortDatas();

private:
	QList<lh::Entity*> _datas{};
};

} // namespace lhe

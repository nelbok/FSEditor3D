#pragma once

#include <QtCore/QAbstractListModel>

#include <lh/data/Project.hpp>

namespace lhe {
class EntityModel : public QAbstractListModel {
	Q_OBJECT

public:
	EntityModel(lh::Project* project, QObject* parent = nullptr);
	virtual ~EntityModel();

	virtual void initDatas() = 0;
	const QList<lh::Entity*>& datas() const;

	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	virtual QHash<int, QByteArray> roleNames() const override;

protected slots:
	virtual void updateDatas() = 0;
	void sortDatas();

protected:
	template<class T>
	void fillDatas(const QList<T*>& datas) {
		// Disconnect
		for (auto* entity : _datas) {
			disconnect(entity, &lh::Entity::isAliveUpdated, this, &EntityModel::updateDatas);
			disconnect(entity, &lh::Entity::nameUpdated, this, &EntityModel::sortDatas);
		}
		_datas.clear();

		// Fill the new model
		for (auto* entity : datas) {
			connect(entity, &lh::Entity::isAliveUpdated, this, &EntityModel::updateDatas);
			if (!entity->isAlive())
				continue;
			_datas.append(entity);
			connect(entity, &lh::Entity::nameUpdated, this, &EntityModel::sortDatas);
		}

		// Sort
		sortDatas();
	}

	lh::Project* _project{ nullptr };
	QList<lh::Entity*> _datas{};
};

} // namespace lhe

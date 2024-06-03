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
			disconnectData(entity);
		}
		_datas.clear();

		// Fill the new model
		for (auto* entity : datas) {
			if (!entity->isAlive())
				continue;
			connectData(entity);
			_datas.append(entity);
		}

		// Sort
		sortDatas();
	}

	virtual void disconnectData(lh::Entity* entity);
	virtual void connectData(lh::Entity* entity);

protected:
	lh::Project* _project{ nullptr };

private:
	QList<lh::Entity*> _datas{};
};

} // namespace lhe

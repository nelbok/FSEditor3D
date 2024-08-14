#pragma once

#include <QtCore/QAbstractListModel>

#include <fsd/data/Project.hpp>

namespace fse {
class EntityModel : public QAbstractListModel {
	Q_OBJECT

public:
	EntityModel(fsd::Project* project, QObject* parent = nullptr);
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
			connectData(entity);
			if (!entity->isAlive())
				continue;
			_datas.append(entity);
		}

		// Sort
		sortDatas();
	}

	virtual void disconnectData(fsd::Entity* entity);
	virtual void connectData(fsd::Entity* entity);

protected:
	fsd::Project* _project{ nullptr };

private:
	QList<fsd::Entity*> _datas{};
};

} // namespace fse

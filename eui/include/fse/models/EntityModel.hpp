#pragma once

#include <QtCore/QAbstractListModel>

#include <fsd/data/Project.hpp>

namespace fse {
class EntityModel : public QAbstractListModel {
	Q_OBJECT
	Q_PROPERTY(bool hasNoneOption READ hasNoneOption WRITE setHasNoneOption NOTIFY hasNoneOptionUpdated)

public:
	EntityModel(fsd::Project* project, QObject* parent = nullptr);
	~EntityModel() override;

	bool hasNoneOption() const;
	void setHasNoneOption(bool hasNoneOption);

	virtual void initDatas() = 0;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QHash<int, QByteArray> roleNames() const override;

protected slots:
	virtual void updateDatas() = 0;
	void sortDatas();

protected:
	template<class T>
	void fillDatas(fsd::Container<T>* datas) {
		// Disconnect
		for (auto* entity : _datas) {
			if (entity)
				disconnectData(entity);
		}
		_datas.clear();

		// Fill the new model
		if (_hasNoneOption)
			_datas.append(nullptr);
		for (auto* entity : datas->get()) {
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
	bool _hasNoneOption{ false };

signals:
	void hasNoneOptionUpdated();
};

} // namespace fse

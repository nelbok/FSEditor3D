#include "EntityModel.hpp"

namespace lhe {

EntityModel::EntityModel(QObject* parent)
	: QAbstractListModel(parent) {}

EntityModel::~EntityModel() {}

const QList<lh::Entity*>& EntityModel::datas() const {
	return _datas;
}

constexpr auto rName = Qt::UserRole + 1;
constexpr auto rUuid = Qt::UserRole + 2;

int EntityModel::rowCount(const QModelIndex&) const {
	return _datas.size();
}

QVariant EntityModel::data(const QModelIndex& index, int role) const {
	if (index.row() < 0 || index.row() >= _datas.count())
		return QVariant();

	switch (role) {
		case rName:
			return _datas.at(index.row())->name();
		case rUuid:
			return _datas.at(index.row())->uuid();
		default:
			return {};
	}
	return {};
}

QHash<int, QByteArray> EntityModel::roleNames() const {
	QHash<int, QByteArray> roles;
	roles[rName] = "name";
	roles[rUuid] = "uuid";
	return roles;
}

void EntityModel::sortDatas() {
	beginResetModel();
	std::sort(_datas.begin(), _datas.end(), [](lh::Entity* p1, lh::Entity* p2) {
		return p1->name().toLower() < p2->name().toLower();
	});
	endResetModel();
}

} // namespace lhe

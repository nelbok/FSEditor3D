#include "EntityModel.hpp"

namespace lhe {

EntityModel::EntityModel(lh::Project* project, QObject* parent)
	: QAbstractListModel(parent)
	, _project{ project } {
	assert(_project);
}

EntityModel::~EntityModel() {}

int EntityModel::rowCount(const QModelIndex&) const {
	return _datas.size();
}

QVariant EntityModel::data(const QModelIndex& index, int role) const {
	if (index.row() < 0 || index.row() >= _datas.count())
		return {};

	// Special case: entity
	if (role == Qt::UserRole + 1) {
		return QVariant::fromValue(_datas.at(index.row()));
	}

	const auto& roles = roleNames();
	if (roles.contains(role)) {
		return _datas.at(index.row())->property(roles.value(role));
	}

	return {};
}

QHash<int, QByteArray> EntityModel::roleNames() const {
	QHash<int, QByteArray> roles;
	roles[Qt::UserRole + 1] = "entity";
	roles[Qt::UserRole + 2] = "uuid";
	roles[Qt::UserRole + 3] = "name";
	return roles;
}

void EntityModel::sortDatas() {
	beginResetModel();
	std::sort(_datas.begin(), _datas.end(), [](lh::Entity* p1, lh::Entity* p2) {
		return p1->name().toLower() < p2->name().toLower();
	});
	endResetModel();
}

void EntityModel::disconnectData(lh::Entity* entity) {
	disconnect(entity, &lh::Entity::isAliveUpdated, this, &EntityModel::updateDatas);
	disconnect(entity, &lh::Entity::nameUpdated, this, &EntityModel::sortDatas);
}

void EntityModel::connectData(lh::Entity* entity) {
	connect(entity, &lh::Entity::isAliveUpdated, this, &EntityModel::updateDatas);
	connect(entity, &lh::Entity::nameUpdated, this, &EntityModel::sortDatas);
}

} // namespace lhe

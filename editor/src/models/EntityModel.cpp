#include "EntityModel.hpp"

namespace fse {

EntityModel::EntityModel(fsd::Project* project, QObject* parent)
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
	std::sort(_datas.begin(), _datas.end(), [](fsd::Entity* p1, fsd::Entity* p2) {
		return p1->name().toLower() < p2->name().toLower();
	});
	endResetModel();
}

void EntityModel::disconnectData(fsd::Entity* entity) {
	disconnect(entity, &fsd::Entity::isAliveUpdated, this, &EntityModel::updateDatas);
	disconnect(entity, &fsd::Entity::nameUpdated, this, &EntityModel::sortDatas);
}

void EntityModel::connectData(fsd::Entity* entity) {
	connect(entity, &fsd::Entity::isAliveUpdated, this, &EntityModel::updateDatas);
	connect(entity, &fsd::Entity::nameUpdated, this, &EntityModel::sortDatas);
}

} // namespace fse

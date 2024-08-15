#include "EntityModel.hpp"

#include <QtCore/QCoreApplication>

namespace fse {

EntityModel::EntityModel(fsd::Project* project, QObject* parent)
	: QAbstractListModel(parent)
	, _project{ project } {
	assert(_project);
}

EntityModel::~EntityModel() {}

bool EntityModel::hasNoneOption() const {
	return _hasNoneOption;
}

void EntityModel::setHasNoneOption(bool hasNoneOption) {
	if (_hasNoneOption != hasNoneOption) {
		_hasNoneOption = hasNoneOption;
		updateDatas();
		emit hasNoneOptionUpdated();
	}
}

int EntityModel::rowCount(const QModelIndex&) const {
	return _datas.size();
}

constexpr auto lEntity = 0;
constexpr auto lName = 1;

QVariant EntityModel::data(const QModelIndex& index, int role) const {
	if (index.row() < 0 || index.row() >= _datas.count())
		return {};

	auto* entity = _datas.at(index.row());

	// Special case: entity
	if (role == lEntity) {
		return QVariant::fromValue(entity);
	}

	const auto& roles = roleNames();
	if (roles.contains(role)) {
		if (entity)
			return entity->property(roles.value(role));
		else if (lName) {
			assert(_hasNoneOption);
			return QCoreApplication::translate("EntityModel", "None");
		}
	}

	return {};
}

QHash<int, QByteArray> EntityModel::roleNames() const {
	QHash<int, QByteArray> roles;
	roles[lEntity] = "entity";
	roles[lName] = "name";
	roles[lName + 1] = "uuid";
	return roles;
}

void EntityModel::sortDatas() {
	beginResetModel();
	std::sort(_datas.begin(), _datas.end(), [](fsd::Entity* p1, fsd::Entity* p2) {
		// hasNoneOption
		if (!p1)
			return true;
		if (!p2)
			return false;

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

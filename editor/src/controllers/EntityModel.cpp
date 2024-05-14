#include "EntityModel.hpp"

#include <lh/data/Character.hpp>

namespace lhe {

EntityModel::EntityModel(QObject* parent)
	: QAbstractListModel(parent) {}

EntityModel::~EntityModel() {}

int EntityModel::currentIndex() const {
	for (int i = 0; i < _model.size(); ++i) {
		if (_model.at(i)->uuid() == _currentUuid) {
			return i;
		}
	}
	return -1;
}

void EntityModel::setCurrentIndex(int currentIndex) {
	if (0 <= currentIndex && currentIndex < _model.size()) {
		_currentUuid = _model.at(currentIndex)->uuid();
	} else {
		_currentUuid = QUuid{};
	}
	emit currentIndexUpdated();
	emit currentDataUpdated();
}

lh::Entity* EntityModel::currentData() const {
	for (auto* entity : _model) {
		if (entity->uuid() == _currentUuid) {
			return entity;
		}
	}
	return nullptr;
}

void EntityModel::setCurrentData(lh::Entity* currentData) {
	if (currentData) {
		if (_currentUuid == currentData->uuid())
			return;
		for (auto* entity : _model) {
			if (entity->uuid() == currentData->uuid()) {
				_currentUuid = currentData->uuid();
				emit currentIndexUpdated();
				emit currentDataUpdated();
				return;
			}
		}
	}
	if (!_currentUuid.isNull()) {
		_currentUuid = QUuid{};
		emit currentIndexUpdated();
		emit currentDataUpdated();
	}
}

const QList<lh::Entity*>& EntityModel::model() const {
	return _model;
}

void EntityModel::setModel(const QList<lh::Entity*>& model) {
	for (auto* entity : _model) {
		disconnect(entity, &lh::Entity::nameUpdated, this, &EntityModel::sort);
	}
	_model = model;
	for (auto* entity : _model) {
		connect(entity, &lh::Entity::nameUpdated, this, &EntityModel::sort);
	}
	sort();
}

constexpr auto rName = Qt::UserRole + 1;
constexpr auto rUuid = Qt::UserRole + 2;

int EntityModel::rowCount(const QModelIndex&) const {
	return _model.size();
}

QVariant EntityModel::data(const QModelIndex& index, int role) const {
	if (index.row() < 0 || index.row() >= _model.count())
		return QVariant();

	switch (role) {
		case rName:
			return _model.at(index.row())->name();
		case rUuid:
			return _model.at(index.row())->uuid();
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

void EntityModel::sort() {
	beginResetModel();
	std::sort(_model.begin(), _model.end(), [](lh::Entity* p1, lh::Entity* p2) {
		return p1->name().toLower() < p2->name().toLower();
	});
	endResetModel();
	emit modelUpdated();
	emit currentIndexUpdated();
	emit currentDataUpdated();
}

} // namespace lhe

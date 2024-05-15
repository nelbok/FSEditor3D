#include "SelectionManager.hpp"

namespace lhe {

SelectionManager::SelectionManager(QObject* parent)
	: QObject(parent) {}

SelectionManager::~SelectionManager() {}

int SelectionManager::currentIndex() const {
	const auto& datas = _model->datas();
	for (int i = 0; i < datas.size(); ++i) {
		if (datas.at(i)->uuid() == _currentUuid) {
			return i;
		}
	}
	return -1;
}

void SelectionManager::setCurrentIndex(int currentIndex) {
	const auto& datas = _model->datas();
	if (0 <= currentIndex && currentIndex < datas.size()) {
		_currentUuid = datas.at(currentIndex)->uuid();
	} else {
		_currentUuid = QUuid{};
	}
	emit currentUpdated();
}

lh::Entity* SelectionManager::currentData() const {
	const auto& datas = _model->datas();
	for (auto* entity : datas) {
		if (entity->uuid() == _currentUuid) {
			return entity;
		}
	}
	return nullptr;
}

void SelectionManager::setCurrentData(lh::Entity* currentData) {
	if (currentData) {
		if (_currentUuid == currentData->uuid())
			return;
		const auto& datas = _model->datas();
		for (auto* entity : datas) {
			if (entity->uuid() == currentData->uuid()) {
				_currentUuid = currentData->uuid();
				emit currentUpdated();
				return;
			}
		}
	}
	if (!_currentUuid.isNull()) {
		_currentUuid = QUuid{};
		emit currentUpdated();
	}
}

EntityModel* SelectionManager::model() const {
	return _model;
}

void SelectionManager::setModel(EntityModel* model) {
	if (_model != model) {
		if (_model) {
			disconnect(model, &EntityModel::modelReset, this, &SelectionManager::currentUpdated);
		}
		_model = model;
		if (_model) {
			connect(model, &EntityModel::modelReset, this, &SelectionManager::currentUpdated);
		}
		emit modelUpdated();
	}
}

} // namespace lhe

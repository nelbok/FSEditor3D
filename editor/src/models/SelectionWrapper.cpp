#include "SelectionWrapper.hpp"

namespace lhe {

SelectionWrapper::SelectionWrapper(QObject* parent)
	: QObject(parent) {}

SelectionWrapper::~SelectionWrapper() {}

int SelectionWrapper::currentIndex() const {
	assert(_model);
	if (!_model)
		return -1;

	for (int i = 0; i < _model->rowCount(); ++i) {
		if (_model->data(_model->index(i, 0), getRole("uuid")) == _currentUuid) {
			return i;
		}
	}
	return -1;
}

void SelectionWrapper::setCurrentIndex(int currentIndex) {
	assert(_model);
	if (0 <= currentIndex && currentIndex < _model->rowCount()) {
		_currentUuid = _model->data(_model->index(currentIndex, 0), getRole("uuid")).toUuid();
	} else {
		_currentUuid = QUuid{};
	}
	emit currentUpdated();
}

lh::Entity* SelectionWrapper::currentData() const {
	assert(_model);
	for (int i = 0; i < _model->rowCount(); ++i) {
		const auto& index = _model->index(i, 0);
		if (_model->data(index, getRole("uuid")) == _currentUuid) {
			return _model->data(index, getRole("entity")).value<lh::Entity*>();
		}
	}

	return nullptr;
}

void SelectionWrapper::setCurrentData(lh::Entity* currentData) {
	assert(_model);
	if (_model && currentData) {
		if (_currentUuid == currentData->uuid())
			return;
		for (int i = 0; i < _model->rowCount(); ++i) {
			if (_model->data(_model->index(i, 0), getRole("uuid")) == currentData->uuid()) {
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

QAbstractItemModel* SelectionWrapper::model() const {
	return _model;
}

void SelectionWrapper::setModel(QAbstractItemModel* model) {
	if (_model != model) {
		if (_model) {
			disconnect(model, &QAbstractItemModel::modelReset, this, &SelectionWrapper::currentUpdated);
		}
		_model = model;
		if (_model) {
			connect(model, &QAbstractItemModel::modelReset, this, &SelectionWrapper::currentUpdated);
		}
		emit modelUpdated();
	}
}

int SelectionWrapper::getRole(const QByteArray& name) const {
	assert(_model);
	const auto& roles = _model->roleNames();
	for (auto it = roles.cbegin(), end = roles.cend(); it != end; ++it) {
		if (it.value() == name) {
			return it.key();
		}
	}
	assert(false);
	return -1;
}

} // namespace lhe

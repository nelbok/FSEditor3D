#include "SelectionWrapper.hpp"

namespace fse {

SelectionWrapper::SelectionWrapper(QObject* parent)
	: QObject(parent) {}

SelectionWrapper::~SelectionWrapper() {}

int SelectionWrapper::currentIndex() const {
	if (!_model || !_currentData || !_currentData->isAlive())
		return -1;

	for (int i = 0; i < _model->rowCount(); ++i) {
		if (_model->data(_model->index(i, 0), getRole("entity")).value<fsd::Entity*>() == _currentData) {
			return i;
		}
	}
	return -1;
}

void SelectionWrapper::setCurrentIndex(int currentIndex) {
	assert(_model);
	if (0 <= currentIndex && currentIndex < _model->rowCount()) {
		_currentData = _model->data(_model->index(currentIndex, 0), getRole("entity")).value<fsd::Entity*>();
	} else {
		_currentData = nullptr;
	}
	emit currentUpdated();
}

fsd::Entity* SelectionWrapper::currentData() const {
	if (!_model || !_currentData || !_currentData->isAlive())
		return nullptr;

	return _currentData;
}

void SelectionWrapper::setCurrentData(fsd::Entity* currentData) {
	assert(_model);
	if (_currentData != currentData) {
		_currentData = currentData;
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

} // namespace fse

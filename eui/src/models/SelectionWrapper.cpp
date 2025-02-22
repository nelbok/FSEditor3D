#include <fse/models/SelectionWrapper.hpp>

#include <fse/models/EntityModel.hpp>
#include <fse/models/ProxyModel.hpp>

namespace fse {

SelectionWrapper::SelectionWrapper(QObject* parent)
	: QObject(parent) {}

SelectionWrapper::~SelectionWrapper() = default;

int SelectionWrapper::currentIndex() const {
	if (!hasCurrentSelection())
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
	if (!hasCurrentSelection())
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
			QObject::disconnect(model, &QAbstractItemModel::modelReset, this, &SelectionWrapper::currentUpdated);
		}
		_model = model;
		if (_model) {
			QObject::connect(model, &QAbstractItemModel::modelReset, this, &SelectionWrapper::currentUpdated);
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
	assert(!"Unknown role");
	return -1;
}

bool SelectionWrapper::hasCurrentSelection() const {
	if (!_model)
		return false;

	if (_currentData && _currentData->isAlive())
		return true;

	if (const auto* entityModel = qobject_cast<EntityModel*>(_model))
		return entityModel->hasNoneOption();

	if (const auto* proxyModel = qobject_cast<ProxyModel*>(_model))
		if (const auto* entityModel = qobject_cast<EntityModel*>(proxyModel->sourceModel()))
			return entityModel->hasNoneOption();

	return false;
}


} // namespace fse

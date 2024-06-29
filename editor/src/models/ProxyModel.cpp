#include "ProxyModel.hpp"

namespace fse {

ProxyModel::ProxyModel(QObject* parent)
	: QSortFilterProxyModel(parent) {}

ProxyModel::~ProxyModel() {}

const QVariantMap& ProxyModel::filters() const {
	return _filters;
}

void ProxyModel::setFilters(const QVariantMap& filters) {
	if (_filters != filters) {
		_filters = filters;
		invalidateFilter();
		emit filtersUpdated();
	}
}

bool ProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const {
	const auto& index = sourceModel()->index(sourceRow, 0, sourceParent);

	for (auto it = _filters.cbegin(); it != _filters.cend(); ++it) {
		if (sourceModel()->data(index, getRole(it.key().toUtf8())) != it.value())
			return false;
	}

	return true;
}

int ProxyModel::getRole(const QByteArray& name) const {
	const auto& roles = sourceModel()->roleNames();
	for (auto it = roles.cbegin(); it != roles.cend(); ++it) {
		if (it.value() == name) {
			return it.key();
		}
	}
	assert(false);
	return -1;
}

} // namespace fse

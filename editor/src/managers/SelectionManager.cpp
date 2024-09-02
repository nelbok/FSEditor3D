#include <fse/managers/SelectionManager.hpp>

namespace fse {
struct SelectionManager::Impl {
	Type currentType{ Type::None };
	fsd::Link* currentLink{ nullptr };
	fsd::Model* currentModel{ nullptr };
	fsd::Object* currentObject{ nullptr };
	fsd::Place* currentPlace{ nullptr };
};

SelectionManager::SelectionManager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

SelectionManager::~SelectionManager() {}

void SelectionManager::reset() {
	setCurrentType(Type::None);
	setCurrentLink(nullptr);
	setCurrentModel(nullptr);
	setCurrentObject(nullptr);
	setCurrentPlace(nullptr);
}

SelectionManager::Type SelectionManager::currentType() const {
	return _impl->currentType;
}

void SelectionManager::setCurrentType(const Type current) {
	if (_impl->currentType != current) {
		_impl->currentType = current;
		emit currentTypeUpdated();
	}
}

fsd::Link* SelectionManager::currentLink() const {
	return _impl->currentLink;
}

void SelectionManager::setCurrentLink(fsd::Link* current) {
	if (_impl->currentLink != current) {
		_impl->currentLink = current;
		emit currentLinkUpdated();
	}
}

fsd::Model* SelectionManager::currentModel() const {
	return _impl->currentModel;
}

void SelectionManager::setCurrentModel(fsd::Model* current) {
	if (_impl->currentModel != current) {
		_impl->currentModel = current;
		emit currentModelUpdated();
	}
}

fsd::Object* SelectionManager::currentObject() const {
	return _impl->currentObject;
}

void SelectionManager::setCurrentObject(fsd::Object* current) {
	if (_impl->currentObject != current) {
		_impl->currentObject = current;
		emit currentObjectUpdated();
	}
}

fsd::Place* SelectionManager::currentPlace() const {
	return _impl->currentPlace;
}

void SelectionManager::setCurrentPlace(fsd::Place* current) {
	if (_impl->currentPlace != current) {
		_impl->currentPlace = current;
		emit currentPlaceUpdated();
	}
}
} // namespace fse

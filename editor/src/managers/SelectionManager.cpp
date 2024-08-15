#include "SelectionManager.hpp"

#include <fsd/data/Project.hpp>

namespace fse {
struct SelectionManager::Impl {
	Type currentType{ Type::None };
	fsd::Project* project{ nullptr };
	fsd::Link* currentLink{ nullptr };
	fsd::Model* currentModel{ nullptr };
	fsd::Object* currentObject{ nullptr };
	fsd::Place* currentPlace{ nullptr };
};

SelectionManager::SelectionManager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

SelectionManager::~SelectionManager() {}

void SelectionManager::init(fsd::Project* project) {
	assert(!_impl->project);
	assert(project);
	_impl->project = project;
	QObject::connect(project, &fsd::Project::defaultPlaceUpdated, this, &SelectionManager::mainModelUpdated);
}

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
		disconnect();
		_impl->currentType = current;
		connect();
		emit currentTypeUpdated();
		emit mainModelUpdated();
	}
}

fsd::Link* SelectionManager::currentLink() const {
	return _impl->currentLink;
}

void SelectionManager::setCurrentLink(fsd::Link* current) {
	if (_impl->currentLink != current) {
		disconnect();
		_impl->currentLink = current;
		connect();
		emit currentLinkUpdated();
		if (_impl->currentType == Type::Links)
			emit mainModelUpdated();
	}
}

fsd::Model* SelectionManager::currentModel() const {
	return _impl->currentModel;
}

void SelectionManager::setCurrentModel(fsd::Model* current) {
	if (_impl->currentModel != current) {
		disconnect();
		_impl->currentModel = current;
		connect();
		emit currentModelUpdated();
		if (_impl->currentType == Type::Models)
			emit mainModelUpdated();
	}
}

fsd::Object* SelectionManager::currentObject() const {
	return _impl->currentObject;
}

void SelectionManager::setCurrentObject(fsd::Object* current) {
	if (_impl->currentObject != current) {
		disconnect();
		_impl->currentObject = current;
		connect();
		emit currentObjectUpdated();
		if (_impl->currentType == Type::Objects)
			emit mainModelUpdated();
	}
}

fsd::Place* SelectionManager::currentPlace() const {
	return _impl->currentPlace;
}

void SelectionManager::setCurrentPlace(fsd::Place* current) {
	if (_impl->currentPlace != current) {
		disconnect();
		_impl->currentPlace = current;
		connect();
		emit currentPlaceUpdated();
		if (_impl->currentType == Type::Places)
			emit mainModelUpdated();
	}
}

fsd::Model* SelectionManager::mainModel() const {
	assert(_impl->project);
	switch (_impl->currentType) {
		case Type::None:
		case Type::Project:
			if (auto* place = _impl->project->defaultPlace(); place) {
				return place->model();
			}
			break;
		case Type::Models:
			return _impl->currentModel;
			break;
		case Type::Places:
			if (_impl->currentPlace)
				return _impl->currentPlace->model();
			break;
		case Type::Objects:
			if (_impl->currentObject)
				return _impl->currentObject->model();
			break;
		case Type::Links:
			if (_impl->currentLink)
				return _impl->currentLink->model();
			break;
		default:
			break;
	}

	return nullptr;
}

void SelectionManager::disconnect() {
	switch (_impl->currentType) {
		case Type::Places:
			if (_impl->currentPlace)
				QObject::disconnect(_impl->currentPlace, &fsd::Place::modelUpdated, this, &SelectionManager::mainModelUpdated);
			break;
		case Type::Objects:
			if (_impl->currentObject)
				QObject::disconnect(_impl->currentObject, &fsd::Object::modelUpdated, this, &SelectionManager::mainModelUpdated);
			break;
		case Type::Links:
			if (_impl->currentLink)
				QObject::disconnect(_impl->currentLink, &fsd::Link::modelUpdated, this, &SelectionManager::mainModelUpdated);
			break;
		default:
			break;
	}
}

void SelectionManager::connect() {
	switch (_impl->currentType) {
		case Type::Places:
			if (_impl->currentPlace)
				QObject::connect(_impl->currentPlace, &fsd::Place::modelUpdated, this, &SelectionManager::mainModelUpdated);
			break;
		case Type::Objects:
			if (_impl->currentObject)
				QObject::connect(_impl->currentObject, &fsd::Object::modelUpdated, this, &SelectionManager::mainModelUpdated);
			break;
		case Type::Links:
			if (_impl->currentLink)
				QObject::connect(_impl->currentLink, &fsd::Link::modelUpdated, this, &SelectionManager::mainModelUpdated);
			break;
		default:
			break;
	}
}

} // namespace fse

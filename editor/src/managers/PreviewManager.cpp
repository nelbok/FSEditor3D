#include "PreviewManager.hpp"

#include "SelectionManager.hpp"

namespace fse {
struct PreviewManager::Impl {
	fsd::Project* project{ nullptr };
	SelectionManager* manager{ nullptr };
	QList<QMetaObject::Connection> connections;
};

PreviewManager::PreviewManager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

PreviewManager::~PreviewManager() {}

void PreviewManager::init(fsd::Project* project, SelectionManager* manager) {
	assert(!_impl->project);
	assert(!_impl->manager);

	_impl->project = project;
	_impl->manager = manager;

	QObject::connect(project, &fsd::Project::defaultPlaceUpdated, this, &PreviewManager::previewUpdated);
	QObject::connect(manager, &SelectionManager::currentTypeUpdated, this, &PreviewManager::updateConnections);
	QObject::connect(manager, &SelectionManager::currentObjectUpdated, this, &PreviewManager::updateConnections);
	QObject::connect(manager, &SelectionManager::currentPlaceUpdated, this, &PreviewManager::updateConnections);
	QObject::connect(manager, &SelectionManager::currentLinkUpdated, this, &PreviewManager::updateConnections);
	QObject::connect(manager, &SelectionManager::currentModelUpdated, this, &PreviewManager::updateConnections);

	updateConnections();
}

fsd::Geometry* PreviewManager::mainGeometry() const {
	assert(_impl->project);
	assert(_impl->manager);
	switch (_impl->manager->currentType()) {
		case SelectionManager::Type::None:
		case SelectionManager::Type::Project:
			return _impl->project->defaultPlace();
		case SelectionManager::Type::Models:
			return _impl->manager->currentModel();
		case SelectionManager::Type::Places:
			return _impl->manager->currentPlace();
		case SelectionManager::Type::Objects:
			return _impl->manager->currentObject();
		case SelectionManager::Type::Links:
			return _impl->manager->currentLink();
		default:
			break;
	}
	return nullptr;
}

fsd::Model* PreviewManager::mainModel() const {
	assert(_impl->project);
	assert(_impl->manager);
	switch (_impl->manager->currentType()) {
		case SelectionManager::Type::None:
		case SelectionManager::Type::Project:
			if (auto* place = _impl->project->defaultPlace()) {
				return place->model();
			}
			break;
		case SelectionManager::Type::Models:
			return _impl->manager->currentModel();
		case SelectionManager::Type::Places:
			if (_impl->manager->currentPlace())
				return _impl->manager->currentPlace()->model();
			break;
		case SelectionManager::Type::Objects:
			if (_impl->manager->currentObject())
				return _impl->manager->currentObject()->model();
			break;
		case SelectionManager::Type::Links:
			if (_impl->manager->currentLink())
				return _impl->manager->currentLink()->model();
			break;
		default:
			break;
	}
	return nullptr;
}

void PreviewManager::updateConnections() {
	for (const auto& connection : _impl->connections) {
		assert(disconnect(connection));
	}
	_impl->connections.clear();

	switch (_impl->manager->currentType()) {
		case SelectionManager::Type::Models:
			if (_impl->manager->currentModel())
				_impl->connections.append(connect(_impl->manager->currentModel(), &fsd::Model::qmlNameUpdated, this, &PreviewManager::previewUpdated));
			break;
		case SelectionManager::Type::Places:
			if (_impl->manager->currentPlace())
				_impl->connections.append(connect(_impl->manager->currentPlace(), &fsd::Place::modelUpdated, this, &PreviewManager::previewUpdated));
			break;
		case SelectionManager::Type::Objects:
			if (_impl->manager->currentObject())
				_impl->connections.append(connect(_impl->manager->currentObject(), &fsd::Object::modelUpdated, this, &PreviewManager::previewUpdated));
			break;
		case SelectionManager::Type::Links:
			if (_impl->manager->currentLink())
				_impl->connections.append(connect(_impl->manager->currentLink(), &fsd::Link::modelUpdated, this, &PreviewManager::previewUpdated));
			break;
		default:
			break;
	}

	emit previewUpdated();
}
} // namespace fse

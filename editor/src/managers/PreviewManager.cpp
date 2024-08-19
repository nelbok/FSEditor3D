#include "PreviewManager.hpp"

#include <fsd/data/Model.hpp>
#include <fsd/data/Project.hpp>
#include <fsd/data/Shape.hpp>

#include "SelectionManager.hpp"
#include "Manager.hpp"

namespace fse {
constexpr QVector3D lCameraPosition{ 0, 800, 1000 };
constexpr QVector3D lCameraRotation{ -30, 0, 0 };

struct PreviewManager::Impl {
	Manager* manager{ nullptr };
	QList<QMetaObject::Connection> connections;
	QVector3D cameraPosition{};
	QVector3D cameraRotation{};
};

PreviewManager::PreviewManager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

PreviewManager::~PreviewManager() {}

void PreviewManager::init(Manager* manager) {
	assert(!_impl->manager);

	_impl->manager = manager;

	QObject::connect(manager->selectionManager(), &SelectionManager::currentTypeUpdated, this, &PreviewManager::updateConnections);
	QObject::connect(manager->selectionManager(), &SelectionManager::currentObjectUpdated, this, &PreviewManager::updateConnections);
	QObject::connect(manager->selectionManager(), &SelectionManager::currentPlaceUpdated, this, &PreviewManager::updateConnections);
	QObject::connect(manager->selectionManager(), &SelectionManager::currentLinkUpdated, this, &PreviewManager::updateConnections);
	QObject::connect(manager->selectionManager(), &SelectionManager::currentModelUpdated, this, &PreviewManager::updateConnections);

	updateConnections();
}

void PreviewManager::reset() {
	setCameraPosition(lCameraPosition);
	setCameraRotation(lCameraRotation);
}

const QVector3D& PreviewManager::cameraPosition() const {
	return _impl->cameraPosition;
}

void PreviewManager::setCameraPosition(const QVector3D& cameraPosition) {
	if (_impl->cameraPosition != cameraPosition) {
		_impl->cameraPosition = cameraPosition;
		emit cameraPositionUpdated();
	}
}

const QVector3D& PreviewManager::cameraRotation() const {
	return _impl->cameraRotation;
}

void PreviewManager::setCameraRotation(const QVector3D& cameraRotation) {
	if (_impl->cameraRotation != cameraRotation) {
		_impl->cameraRotation = cameraRotation;
		emit cameraRotationUpdated();
	}
}

void PreviewManager::centerOnCurrent() {
	auto position = lCameraPosition;

	const auto& sm = _impl->manager->selectionManager();
	switch (sm->currentType()) {
		case SelectionManager::Type::None:
		case SelectionManager::Type::Project:
			if (auto* place = _impl->manager->project()->defaultPlace())
				position += place->globalPosition();
			break;
		case SelectionManager::Type::Models:
			if (sm->currentModel())
				position += sm->currentModel()->globalPosition();
			break;
		case SelectionManager::Type::Places:
			if (sm->currentPlace())
				position += sm->currentPlace()->globalPosition();
			break;
		case SelectionManager::Type::Objects:
			if (sm->currentObject())
				position += sm->currentObject()->globalPosition();
			break;
		case SelectionManager::Type::Links:
			if (sm->currentLink())
				position += sm->currentLink()->globalPosition();
			break;
		default:
			break;
	}

	setCameraPosition(position);
	setCameraRotation(lCameraRotation);
}

QList<PreviewData> PreviewManager::datas() const {
	QList<PreviewData> datas;

	const auto& sm = _impl->manager->selectionManager();
	switch (sm->currentType()) {
		case SelectionManager::Type::None:
		case SelectionManager::Type::Project:
			if (auto* place = _impl->manager->project()->defaultPlace())
				fillDatas(datas, place, true);
			break;
		case SelectionManager::Type::Models:
			if (sm->currentModel())
				fillDatas(datas, sm->currentModel());
			break;
		case SelectionManager::Type::Places:
			if (sm->currentPlace())
				fillDatas(datas, sm->currentPlace(), true);
			break;
		case SelectionManager::Type::Objects:
			if (sm->currentObject())
				fillDatas(datas, sm->currentObject());
			break;
		case SelectionManager::Type::Links:
			if (sm->currentLink())
				fillDatas(datas, sm->currentLink());
			break;
		default:
			break;
	}

	return datas;
}

void PreviewManager::fillDatas(QList<PreviewData>& datas, fsd::Geometry* geometry, bool useRefs) const {
	// Add others entities if needed
	if (auto* placement = qobject_cast<fsd::Placement*>(geometry)) {
		fillDatas(datas, placement->place());
	}
	if (useRefs) {
		for (auto* entity : geometry->refs()) {
			if (auto* subGeometry = qobject_cast<fsd::Geometry*>(entity))
				fillDatas(datas, subGeometry);
		}
	}

	// Search model for the geometry
	fsd::Model* model = nullptr;
	if (auto* shape = qobject_cast<fsd::Shape*>(geometry)) {
		model = shape->model();
	} else {
		model = qobject_cast<fsd::Model*>(geometry);
	}

	// Add only if there is a valid model
	if (model && model->qmlName() != "") {
		datas.append({ geometry, _impl->manager->balsam()->qmlPath(model) });
	}
}

void PreviewManager::updateConnections() {
	for (const auto& connection : _impl->connections) {
		QObject::disconnect(connection);
	}
	_impl->connections.clear();

	const auto& sm = _impl->manager->selectionManager();
	switch (sm->currentType()) {
		case SelectionManager::Type::None:
		case SelectionManager::Type::Project:
			_impl->connections.append(QObject::connect(_impl->manager->project(), &fsd::Project::defaultPlaceUpdated, this, &PreviewManager::previewUpdated));
			break;
		case SelectionManager::Type::Models:
			if (sm->currentModel())
				_impl->connections.append(QObject::connect(sm->currentModel(), &fsd::Model::qmlNameUpdated, this, &PreviewManager::previewUpdated));
			break;
		case SelectionManager::Type::Places:
			if (sm->currentPlace())
				_impl->connections.append(QObject::connect(sm->currentPlace(), &fsd::Place::modelUpdated, this, &PreviewManager::previewUpdated));
			break;
		case SelectionManager::Type::Objects:
			if (sm->currentObject()) {
				_impl->connections.append(QObject::connect(sm->currentObject(), &fsd::Object::modelUpdated, this, &PreviewManager::previewUpdated));
				_impl->connections.append(QObject::connect(sm->currentObject(), &fsd::Object::placeUpdated, this, &PreviewManager::previewUpdated));
			}
			break;
		case SelectionManager::Type::Links:
			if (sm->currentLink()) {
				_impl->connections.append(QObject::connect(sm->currentLink(), &fsd::Link::modelUpdated, this, &PreviewManager::previewUpdated));
				_impl->connections.append(QObject::connect(sm->currentLink(), &fsd::Link::placeUpdated, this, &PreviewManager::previewUpdated));
			}
			break;
		default:
			break;
	}

	emit previewUpdated();
}
} // namespace fse

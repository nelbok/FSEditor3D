#include <fse/managers/PreviewManager.hpp>

#include <fsd/data/Model.hpp>
#include <fsd/data/Project.hpp>
#include <fsd/data/Shape.hpp>

#include <fse/managers/SelectionManager.hpp>
#include <fse/Manager.hpp>

#include "tools/DefaultSettings.hpp"

namespace fse {
constexpr QVector3D lCameraPosition{ 0, 800, 1000 };
constexpr QVector3D lCameraRotation{ -30, 0, 0 };

struct PreviewManager::Impl {
	Manager* manager{ nullptr };
	QList<QMetaObject::Connection> connections;
	QVector3D cameraPosition{};
	QVector3D cameraRotation{};
	bool areOtherDatasVisible{ fse::DefaultSettings::previewAreOtherDatasVisibleValue };
	bool areOriginsVisible{ fse::DefaultSettings::previewAreOriginsVisibleValue };
	bool isWorldMapVisible{ fse::DefaultSettings::previewIsWorldMapVisibleValue };
};

PreviewManager::PreviewManager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

PreviewManager::~PreviewManager() = default;

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

bool PreviewManager::areOtherDatasVisible() const {
	return _impl->areOtherDatasVisible;
}

void PreviewManager::setAreOtherDatasVisible(bool visible) {
	if (_impl->areOtherDatasVisible != visible) {
		switchOtherDatasVisible();
	}
}

bool PreviewManager::areOriginsVisible() const {
	return _impl->areOriginsVisible;
}

void PreviewManager::setAreOriginsVisible(bool visible) {
	if (_impl->areOriginsVisible != visible) {
		switchOriginsVisible();
	}
}

void PreviewManager::setIsWorldMapVisible(bool visible) {
	if (_impl->isWorldMapVisible != visible) {
		switchWorldMapVisible();
	}
}

bool PreviewManager::isWorldMapVisible() const {
	return _impl->isWorldMapVisible;
}

void PreviewManager::centerOnCurrent() {
	auto position = lCameraPosition;

	switch (const auto& sm = _impl->manager->selectionManager(); sm->currentType()) {
		case SelectionManager::Type::None:
		case SelectionManager::Type::Project:
			if (const auto* place = _impl->manager->project()->defaultPlace())
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

void PreviewManager::switchOtherDatasVisible() {
	_impl->areOtherDatasVisible = !_impl->areOtherDatasVisible;
	emit areOtherDatasVisibleUpdated();
	emit previewUpdated();
}

void PreviewManager::switchOriginsVisible() {
	_impl->areOriginsVisible = !_impl->areOriginsVisible;
	emit areOriginsVisibleUpdated();
}

void PreviewManager::switchWorldMapVisible() {
	_impl->isWorldMapVisible = !_impl->isWorldMapVisible;
	emit isWorldMapVisibleUpdated();
	emit previewUpdated();
}

QList<PreviewData> PreviewManager::datas() const {
	QList<PreviewData> datas;
	QList<fsd::Geometry*> parsed;

	switch (const auto& sm = _impl->manager->selectionManager(); sm->currentType()) {
		case SelectionManager::Type::None:
			if (auto* place = _impl->manager->project()->defaultPlace()) {
				if (_impl->isWorldMapVisible)
					fullMapDatas(datas, parsed, place);
				else
					fillDatas(datas, parsed, place, true);
			}
			break;
		case SelectionManager::Type::Project:
			if (auto* place = _impl->manager->project()->defaultPlace())
				fillDatas(datas, parsed, place, true);
			break;
		case SelectionManager::Type::Models:
			if (sm->currentModel())
				fillDatas(datas, parsed, sm->currentModel());
			break;
		case SelectionManager::Type::Places:
			if (sm->currentPlace())
				fillDatas(datas, parsed, sm->currentPlace(), true);
			break;
		case SelectionManager::Type::Objects:
			if (sm->currentObject())
				fillDatas(datas, parsed, sm->currentObject());
			break;
		case SelectionManager::Type::Links:
			if (sm->currentLink())
				fillDatas(datas, parsed, sm->currentLink());
			break;
		default:
			break;
	}

	return datas;
}

void PreviewManager::fullMapDatas(QList<PreviewData>& datas, QList<fsd::Geometry*>& parsed, fsd::Place* place, const QVector3D& offset) const {
	fillDatas(datas, parsed, place, offset, true);
	for (auto* entity : place->refs()) {
		if (const auto* linkA = qobject_cast<fsd::Link*>(entity))
			if (const auto* linkB = linkA->link())
				if (auto* placeB = linkB->place()) {
					if (parsed.contains(placeB))
						continue;
					fullMapDatas(datas, parsed, placeB, offset + linkA->globalPosition() - linkB->globalPosition());
				}
	}
}

void PreviewManager::fillDatas(QList<PreviewData>& datas, QList<fsd::Geometry*>& parsed, fsd::Geometry* geometry, bool useRefs) const {
	fillDatas(datas, parsed, geometry, { 0, 0, 0 }, useRefs);
}

void PreviewManager::fillDatas(QList<PreviewData>& datas, QList<fsd::Geometry*>& parsed, fsd::Geometry* geometry, const QVector3D& offset, bool useRefs) const {
	if (parsed.contains(geometry)) {
		return;
	}
	parsed.append(geometry);

	if (_impl->areOtherDatasVisible) {
		// Add others entities if needed
		if (const auto* placement = qobject_cast<fsd::Placement*>(geometry)) {
			fillDatas(datas, parsed, placement->place(), offset);
		}
		if (useRefs) {
			for (auto* entity : geometry->refs()) {
				if (auto* subGeometry = qobject_cast<fsd::Geometry*>(entity))
					fillDatas(datas, parsed, subGeometry, offset);
			}
		}
	}

	// Search model for the geometry
	fsd::Model* model = nullptr;
	if (const auto* shape = qobject_cast<fsd::Shape*>(geometry)) {
		model = shape->model();
	} else {
		model = qobject_cast<fsd::Model*>(geometry);
	}

	// Add only if there is a valid model
	if (model && model->qmlName() != "") {
		datas.append({ geometry, _impl->manager->balsam()->qmlPath(model), offset });
	}
}

void PreviewManager::updateConnections() {
	for (const auto& connection : _impl->connections) {
		QObject::disconnect(connection);
	}
	_impl->connections.clear();

	switch (const auto& sm = _impl->manager->selectionManager(); sm->currentType()) {
		case SelectionManager::Type::None:
			_impl->connections.append(QObject::connect(_impl->manager->project(), &fsd::Project::entitiesUpdated, this, &PreviewManager::previewUpdated));
			_impl->connections.append(QObject::connect(_impl->manager->project(), &fsd::Project::defaultPlaceUpdated, this, &PreviewManager::previewUpdated));
			break;
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

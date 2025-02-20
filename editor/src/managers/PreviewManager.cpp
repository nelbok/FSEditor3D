#include <fse/managers/PreviewManager.hpp>

#include <fsd/data/Link.hpp>
#include <fsd/data/Model.hpp>
#include <fsd/data/Object.hpp>
#include <fsd/data/Project.hpp>

#include <fse/managers/SelectionManager.hpp>
#include <fse/Manager.hpp>

#include "tools/DefaultSettings.hpp"

namespace fse {
constexpr QVector3D lCameraPosition{ 0, 800, 1000 };
constexpr QVector3D lCameraRotation{ -30, 0, 0 };

struct PreviewManager::Impl {
	Manager* manager{ nullptr };
	QList<PreviewData> datas;
	QList<EntryPointData> entryPointDatas;
	QList<QMetaObject::Connection> connections;
	unsigned height{ fse::DefaultSettings::previewHeightValue };
	QVector3D cameraPosition{};
	QVector3D cameraRotation{};
	bool areLinksVisible{ fse::DefaultSettings::previewAreLinksVisibleValue };
	bool areObjectsVisible{ fse::DefaultSettings::previewAreObjectsVisibleValue };
	bool areOriginsVisible{ fse::DefaultSettings::previewAreOriginsVisibleValue };
	bool isWorldMode{ fse::DefaultSettings::previewIsWorldModeValue };
	bool isDebugMode{ fse::DefaultSettings::previewIsDebugModeValue };
	ViewMode viewMode{ static_cast<ViewMode>(fse::DefaultSettings::previewViewModeValue) };
	bool isGravityEnabled{ fse::DefaultSettings::previewIsGravityEnabledValue };
};

PreviewManager::PreviewManager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

PreviewManager::~PreviewManager() = default;

void PreviewManager::init(Manager* manager) {
	assert(!_impl->manager);

	_impl->manager = manager;

	QObject::connect(manager->selectionManager(), &SelectionManager::currentTypeUpdated, this, &PreviewManager::updateConnections);
	QObject::connect(manager->selectionManager(), &SelectionManager::currentModelUpdated, this, &PreviewManager::updateConnections);
	QObject::connect(manager->selectionManager(), &SelectionManager::currentObjectUpdated, this, &PreviewManager::updateConnections);
	QObject::connect(manager->selectionManager(), &SelectionManager::currentPlaceUpdated, this, &PreviewManager::updateConnections);
	QObject::connect(manager->selectionManager(), &SelectionManager::currentLinkUpdated, this, &PreviewManager::updateConnections);
	QObject::connect(manager->selectionManager(), &SelectionManager::currentEntryPointUpdated, this, &PreviewManager::updateConnections);

	updateConnections();
}

void PreviewManager::reset() {
	setCameraPosition(lCameraPosition);
	setCameraRotation(lCameraRotation);
}

unsigned PreviewManager::height() const {
	return _impl->height;
}

void PreviewManager::setHeight(unsigned height) {
	if (_impl->height != height) {
		_impl->height = height;
		emit heightUpdated();
	}
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

bool PreviewManager::areLinksVisible() const {
	return _impl->areLinksVisible;
}

void PreviewManager::setAreLinksVisible(bool visible) {
	if (_impl->areLinksVisible != visible)
		switchLinksVisible();
}

bool PreviewManager::areObjectsVisible() const {
	return _impl->areObjectsVisible;
}

void PreviewManager::setAreObjectsVisible(bool visible) {
	if (_impl->areObjectsVisible != visible)
		switchObjectsVisible();
}

bool PreviewManager::areOriginsVisible() const {
	return _impl->areOriginsVisible;
}

void PreviewManager::setAreOriginsVisible(bool visible) {
	if (_impl->areOriginsVisible != visible)
		switchOriginsVisible();
}

bool PreviewManager::isWorldMode() const {
	return _impl->isWorldMode;
}

void PreviewManager::setWorldMode(bool enabled) {
	if (_impl->isWorldMode != enabled)
		switchWorldMode();
}

bool PreviewManager::isDebugMode() const {
	return _impl->isDebugMode;
}

void PreviewManager::setDebugMode(bool enabled) {
	if (_impl->isDebugMode != enabled)
		switchDebugMode();
}

PreviewManager::ViewMode PreviewManager::viewMode() const {
	return _impl->viewMode;
}

void PreviewManager::setViewMode(ViewMode viewMode) {
	if (_impl->viewMode != viewMode)
		switchViewMode();
}

bool PreviewManager::isGravityEnabled() const {
	return _impl->isGravityEnabled;
}

void PreviewManager::setGravityEnabled(bool enabled) {
	if (_impl->isGravityEnabled != enabled)
		switchGravity();
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
		case SelectionManager::Type::EntryPoints:
			if (sm->currentEntryPoint())
				position += sm->currentEntryPoint()->position();
			break;
		default:
			break;
	}

	setCameraPosition(position);
	setCameraRotation(lCameraRotation);
}

void PreviewManager::switchLinksVisible() {
	_impl->areLinksVisible = !_impl->areLinksVisible;
	emit areLinksVisibleUpdated();
	updateDatas();
}

void PreviewManager::switchObjectsVisible() {
	_impl->areObjectsVisible = !_impl->areObjectsVisible;
	emit areObjectsVisibleUpdated();
	updateDatas();
}

void PreviewManager::switchOriginsVisible() {
	_impl->areOriginsVisible = !_impl->areOriginsVisible;
	emit areOriginsVisibleUpdated();
}

void PreviewManager::switchWorldMode() {
	_impl->isWorldMode = !_impl->isWorldMode;
	emit isWorldModeUpdated();
	updateDatas();
}

void PreviewManager::switchDebugMode() {
	_impl->isDebugMode = !_impl->isDebugMode;
	emit isDebugModeUpdated();
}

void PreviewManager::switchViewMode() {
	switch (_impl->viewMode) {
		case ViewMode::Design:
			_impl->viewMode = ViewMode::Collide;
			break;
		case ViewMode::Collide:
			_impl->viewMode = ViewMode::Design;
			break;
	}
	emit viewModeUpdated();
}

void PreviewManager::switchGravity() {
	_impl->isGravityEnabled = !_impl->isGravityEnabled;
	emit gravityEnabledUpdated();
}

QList<PreviewData> PreviewManager::datas() const {
	return _impl->datas;
}

QList<EntryPointData> PreviewManager::entryPointDatas() const {
	return _impl->entryPointDatas;
}

void PreviewManager::fullMapDatas(QList<fsd::Geometry*>& parsed, fsd::Place* place, const QVector3D& offset) const {
	fillDatas(parsed, place, offset);
	for (auto* entity : place->refs()) {
		if (const auto* linkA = qobject_cast<fsd::Link*>(entity))
			if (const auto* linkB = linkA->link())
				if (auto* placeB = linkB->place()) {
					if (parsed.contains(placeB))
						continue;
					fullMapDatas(parsed, placeB, offset + linkA->globalPosition() - linkB->globalPosition());
				}
	}
}

void PreviewManager::fillDatas(QList<fsd::Geometry*>& parsed, fsd::Geometry* geometry, const QVector3D& offset) const {
	if (parsed.contains(geometry)) {
		return;
	}
	parsed.append(geometry);

	// If object or link, show place
	if (const auto* placement = qobject_cast<fsd::Placement*>(geometry)) {
		fillDatas(parsed, placement->place(), offset);
	}

	// Adding refs, either links or objects
	if (qobject_cast<fsd::Place*>(geometry)) {
		for (auto* entity : geometry->refs()) {
			// Show links if checked
			if (_impl->areLinksVisible)
				if (auto* link = qobject_cast<fsd::Link*>(entity))
					fillDatas(parsed, link, offset);

			// Show objects if checked
			if (_impl->areObjectsVisible)
				if (auto* object = qobject_cast<fsd::Object*>(entity))
					fillDatas(parsed, object, offset);

			if (auto* entryPoint = qobject_cast<fsd::EntryPoint*>(entity))
				_impl->entryPointDatas.append({ entryPoint, offset });
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
		_impl->datas.append({
			geometry,
			_impl->manager->balsam()->qmlDir(model),
			_impl->manager->balsam()->qmlPath(model),
			offset,
		});
	}
}

void PreviewManager::updateDatas() {
	_impl->datas.clear();
	_impl->entryPointDatas.clear();
	QList<fsd::Geometry*> parsed;

	switch (const auto& sm = _impl->manager->selectionManager(); sm->currentType()) {
		case SelectionManager::Type::Settings:
		case SelectionManager::Type::None:
			if (auto* place = _impl->manager->project()->defaultPlace()) {
				if (_impl->isWorldMode)
					fullMapDatas(parsed, place);
				else
					fillDatas(parsed, place);
			}
			break;
		case SelectionManager::Type::Project:
			setGravityEnabled(false);
			if (auto* place = _impl->manager->project()->defaultPlace())
				fillDatas(parsed, place);
			break;
		case SelectionManager::Type::Models:
			setGravityEnabled(false);
			if (sm->currentModel())
				fillDatas(parsed, sm->currentModel());
			break;
		case SelectionManager::Type::Places:
			setGravityEnabled(false);
			if (sm->currentPlace())
				fillDatas(parsed, sm->currentPlace());
			break;
		case SelectionManager::Type::Objects:
			setGravityEnabled(false);
			if (sm->currentObject())
				fillDatas(parsed, sm->currentObject());
			break;
		case SelectionManager::Type::Links:
			setGravityEnabled(false);
			if (sm->currentLink())
				fillDatas(parsed, sm->currentLink());
			break;
		case SelectionManager::Type::EntryPoints:
			setGravityEnabled(false);
			if (sm->currentEntryPoint() && sm->currentEntryPoint()->place())
				fillDatas(parsed, sm->currentEntryPoint()->place());
			break;
	}

	emit previewUpdated();
}

void PreviewManager::updateConnections() {
	for (const auto& connection : _impl->connections) {
		QObject::disconnect(connection);
	}
	_impl->connections.clear();

	switch (const auto& sm = _impl->manager->selectionManager(); sm->currentType()) {
		case SelectionManager::Type::None:
			_impl->connections.append(QObject::connect(_impl->manager->project(), &fsd::Project::entitiesUpdated, this, &PreviewManager::updateDatas));
			_impl->connections.append(QObject::connect(_impl->manager->project(), &fsd::Project::defaultPlaceUpdated, this, &PreviewManager::updateDatas));
			break;
		case SelectionManager::Type::Project:
			_impl->connections.append(QObject::connect(_impl->manager->project(), &fsd::Project::defaultPlaceUpdated, this, &PreviewManager::updateDatas));
			break;
		case SelectionManager::Type::Models:
			if (sm->currentModel())
				_impl->connections.append(QObject::connect(sm->currentModel(), &fsd::Model::qmlNameUpdated, this, &PreviewManager::updateDatas));
			break;
		case SelectionManager::Type::Places:
			if (sm->currentPlace())
				_impl->connections.append(QObject::connect(sm->currentPlace(), &fsd::Place::modelUpdated, this, &PreviewManager::updateDatas));
			break;
		case SelectionManager::Type::Objects:
			if (sm->currentObject()) {
				_impl->connections.append(QObject::connect(sm->currentObject(), &fsd::Object::modelUpdated, this, &PreviewManager::updateDatas));
				_impl->connections.append(QObject::connect(sm->currentObject(), &fsd::Object::placeUpdated, this, &PreviewManager::updateDatas));
			}
			break;
		case SelectionManager::Type::Links:
			if (sm->currentLink()) {
				_impl->connections.append(QObject::connect(sm->currentLink(), &fsd::Link::modelUpdated, this, &PreviewManager::updateDatas));
				_impl->connections.append(QObject::connect(sm->currentLink(), &fsd::Link::placeUpdated, this, &PreviewManager::updateDatas));
			}
			break;
		case SelectionManager::Type::EntryPoints:
			if (sm->currentEntryPoint())
				_impl->connections.append(QObject::connect(sm->currentEntryPoint(), &fsd::EntryPoint::placeUpdated, this, &PreviewManager::updateDatas));
			break;
		default:
			break;
	}

	updateDatas();
}
} // namespace fse

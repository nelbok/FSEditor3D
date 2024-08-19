#include "PreviewManager.hpp"

#include <fsd/data/Model.hpp>
#include <fsd/data/Project.hpp>
#include <fsd/data/Shape.hpp>

#include "SelectionManager.hpp"
#include "Manager.hpp"

namespace fse {
struct PreviewManager::Impl {
	Manager* manager{ nullptr };
	QList<QMetaObject::Connection> connections;
};

PreviewManager::PreviewManager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

PreviewManager::~PreviewManager() {}

void PreviewManager::init(Manager* manager) {
	assert(!_impl->manager);

	_impl->manager = manager;

	QObject::connect(manager->project(), &fsd::Project::defaultPlaceUpdated, this, &PreviewManager::previewUpdated);
	QObject::connect(manager->selectionManager(), &SelectionManager::currentTypeUpdated, this, &PreviewManager::updateConnections);
	QObject::connect(manager->selectionManager(), &SelectionManager::currentObjectUpdated, this, &PreviewManager::updateConnections);
	QObject::connect(manager->selectionManager(), &SelectionManager::currentPlaceUpdated, this, &PreviewManager::updateConnections);
	QObject::connect(manager->selectionManager(), &SelectionManager::currentLinkUpdated, this, &PreviewManager::updateConnections);
	QObject::connect(manager->selectionManager(), &SelectionManager::currentModelUpdated, this, &PreviewManager::updateConnections);

	updateConnections();
}

QList<PreviewData> PreviewManager::datas() const {
	QList<PreviewData> datas;

	const auto& sm = _impl->manager->selectionManager();
	switch (sm->currentType()) {
		case SelectionManager::Type::None:
		case SelectionManager::Type::Project:
			if (auto* place = _impl->manager->project()->defaultPlace()) {
				fillDatas(datas, place);
			}
			break;
		case SelectionManager::Type::Models:
			fillDatas(datas, sm->currentModel());
			break;
		case SelectionManager::Type::Places:
			fillDatas(datas, sm->currentPlace());
			break;
		case SelectionManager::Type::Objects:
			fillDatas(datas, sm->currentObject());
			break;
		case SelectionManager::Type::Links:
			fillDatas(datas, sm->currentLink());
			break;
		default:
			break;
	}

	return datas;
}

void PreviewManager::fillDatas(QList<PreviewData>& datas, fsd::Geometry* geometry) const {
	// Add others entities if needed
	if (auto* placement = qobject_cast<fsd::Placement*>(geometry)) {
		fillDatas(datas, placement->place());
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
		assert(disconnect(connection));
	}
	_impl->connections.clear();

	const auto& sm = _impl->manager->selectionManager();
	switch (sm->currentType()) {
		case SelectionManager::Type::Models:
			if (sm->currentModel())
				_impl->connections.append(connect(sm->currentModel(), &fsd::Model::qmlNameUpdated, this, &PreviewManager::previewUpdated));
			break;
		case SelectionManager::Type::Places:
			if (sm->currentPlace())
				_impl->connections.append(connect(sm->currentPlace(), &fsd::Place::modelUpdated, this, &PreviewManager::previewUpdated));
			break;
		case SelectionManager::Type::Objects:
			if (sm->currentObject())
				_impl->connections.append(connect(sm->currentObject(), &fsd::Object::modelUpdated, this, &PreviewManager::previewUpdated));
			break;
		case SelectionManager::Type::Links:
			if (sm->currentLink())
				_impl->connections.append(connect(sm->currentLink(), &fsd::Link::modelUpdated, this, &PreviewManager::previewUpdated));
			break;
		default:
			break;
	}

	emit previewUpdated();
}
} // namespace fse

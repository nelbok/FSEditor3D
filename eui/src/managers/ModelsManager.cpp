#include <fse/managers/ModelsManager.hpp>

namespace fse {

struct ModelsManager::Impl {
	EntryPointModel* entryPointModel{ nullptr };
	LinkModel* linkModel{ nullptr };
	ModelModel* modelModel{ nullptr };
	ObjectModel* objectModel{ nullptr };
	PlaceModel* placeModel{ nullptr };

	EntryPointModel* entryPointModelWithNone{ nullptr };
	LinkModel* linkModelWithNone{ nullptr };
	ModelModel* modelModelWithNone{ nullptr };
	ObjectModel* objectModelWithNone{ nullptr };
	PlaceModel* placeModelWithNone{ nullptr };
};

ModelsManager::ModelsManager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

ModelsManager::~ModelsManager() = default;

void ModelsManager::init(fsd::Project* project) {
	assert(project);

	_impl->entryPointModel = new EntryPointModel(project, this);
	_impl->linkModel = new LinkModel(project, this);
	_impl->modelModel = new ModelModel(project, this);
	_impl->objectModel = new ObjectModel(project, this);
	_impl->placeModel = new PlaceModel(project, this);

	_impl->entryPointModel->initDatas();
	_impl->linkModel->initDatas();
	_impl->modelModel->initDatas();
	_impl->objectModel->initDatas();
	_impl->placeModel->initDatas();

	_impl->entryPointModelWithNone = new EntryPointModel(project, this);
	_impl->linkModelWithNone = new LinkModel(project, this);
	_impl->modelModelWithNone = new ModelModel(project, this);
	_impl->objectModelWithNone = new ObjectModel(project, this);
	_impl->placeModelWithNone = new PlaceModel(project, this);

	_impl->entryPointModelWithNone->setHasNoneOption(true);
	_impl->linkModelWithNone->setHasNoneOption(true);
	_impl->modelModelWithNone->setHasNoneOption(true);
	_impl->objectModelWithNone->setHasNoneOption(true);
	_impl->placeModelWithNone->setHasNoneOption(true);

	_impl->entryPointModelWithNone->initDatas();
	_impl->linkModelWithNone->initDatas();
	_impl->modelModelWithNone->initDatas();
	_impl->objectModelWithNone->initDatas();
	_impl->placeModelWithNone->initDatas();
}

EntryPointModel* ModelsManager::entryPointModel() const {
	assert(_impl->entryPointModel);
	return _impl->entryPointModel;
}

LinkModel* ModelsManager::linkModel() const {
	assert(_impl->linkModel);
	return _impl->linkModel;
}

ModelModel* ModelsManager::modelModel() const {
	assert(_impl->modelModel);
	return _impl->modelModel;
}

ObjectModel* ModelsManager::objectModel() const {
	assert(_impl->objectModel);
	return _impl->objectModel;
}

PlaceModel* ModelsManager::placeModel() const {
	assert(_impl->placeModel);
	return _impl->placeModel;
}

EntryPointModel* ModelsManager::entryPointModelWithNone() const {
	assert(_impl->entryPointModelWithNone);
	return _impl->entryPointModelWithNone;
}

LinkModel* ModelsManager::linkModelWithNone() const {
	assert(_impl->linkModelWithNone);
	return _impl->linkModelWithNone;
}

ModelModel* ModelsManager::modelModelWithNone() const {
	assert(_impl->modelModelWithNone);
	return _impl->modelModelWithNone;
}

ObjectModel* ModelsManager::objectModelWithNone() const {
	assert(_impl->objectModelWithNone);
	return _impl->objectModelWithNone;
}

PlaceModel* ModelsManager::placeModelWithNone() const {
	assert(_impl->placeModelWithNone);
	return _impl->placeModelWithNone;
}
} // namespace fse

#include "ModelsManager.hpp"

namespace fse {

struct ModelsManager::Impl {
	LinkModel* linkModel{ nullptr };
	ModelModel* modelModel{ nullptr };
	ObjectModel* objectModel{ nullptr };
	PlaceModel* placeModel{ nullptr };
};

ModelsManager::ModelsManager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

ModelsManager::~ModelsManager() {
}

void ModelsManager::init(fsd::Project* project) {
	assert(project);

	_impl->objectModel = new ObjectModel(project, this);
	_impl->linkModel = new LinkModel(project, this);
	_impl->modelModel = new ModelModel(project, this);
	_impl->placeModel = new PlaceModel(project, this);

	_impl->objectModel->initDatas();
	_impl->linkModel->initDatas();
	_impl->modelModel->initDatas();
	_impl->placeModel->initDatas();
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
} // namespace fse

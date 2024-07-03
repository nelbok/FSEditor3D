#include "ModelsManager.hpp"

namespace fse {

struct ModelsManager::Impl {
	CharacterModel* characterModel{ nullptr };
	LinkModel* linkModel{ nullptr };
	ModelModel* modelModel{ nullptr };
	PlaceModel* placeModel{ nullptr };
};

ModelsManager::ModelsManager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {}

ModelsManager::~ModelsManager() {
}

void ModelsManager::init(fsd::Project* project) {
	assert(project);

	_impl->characterModel = new CharacterModel(project, this);
	_impl->linkModel = new LinkModel(project, this);
	_impl->modelModel = new ModelModel(project, this);
	_impl->placeModel = new PlaceModel(project, this);

	_impl->characterModel->initDatas();
	_impl->linkModel->initDatas();
	_impl->modelModel->initDatas();
	_impl->placeModel->initDatas();
}

CharacterModel* ModelsManager::characterModel() const {
	assert(_impl->characterModel);
	return _impl->characterModel;
}

LinkModel* ModelsManager::linkModel() const {
	assert(_impl->linkModel);
	return _impl->linkModel;
}

ModelModel* ModelsManager::modelModel() const {
	assert(_impl->modelModel);
	return _impl->modelModel;
}

PlaceModel* ModelsManager::placeModel() const {
	assert(_impl->placeModel);
	return _impl->placeModel;
}
} // namespace fse

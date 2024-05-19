#include <lh/data/Model.hpp>

#include <lh/data/Project.hpp>

namespace lh {
struct Model::Impl {};

Model::Model(Project* project)
	: Entity(project)
	, _impl{ std::make_unique<Impl>() } {}

Model::~Model() {}

void Model::reset() {
	Entity::reset();
}

void Model::copy(const Model& model) {
	Entity::copy(model);
}

void Model::load(const QJsonObject& json) {
	Entity::load(json);
}

void Model::save(QJsonObject& json) const {
	Entity::save(json);
}
} // namespace lh

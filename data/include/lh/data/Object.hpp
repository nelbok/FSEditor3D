#pragma once

#include <lh/data/Entity.hpp>

namespace lh {
class Model;
class Project;

class Object : public Entity {
	Q_OBJECT
	Q_PROPERTY(Model* model READ model WRITE setModel NOTIFY modelUpdated)

public:
	Object(Project* project);
	virtual ~Object();

	virtual void reset() override;
	void copy(const Object& link);

	Model* model() const;
	void setModel(Model* model);

	virtual void load(const QJsonObject& json) override;
	virtual void save(QJsonObject& json) const override;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void modelUpdated();
};
} // namespace lh

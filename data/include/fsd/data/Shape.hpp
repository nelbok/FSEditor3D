#pragma once

#include <fsd/data/Geometry.hpp>

namespace fsd {
class Model;
class Project;

class Shape : public Geometry {
	Q_OBJECT
	Q_PROPERTY(Model* model READ model WRITE setModel NOTIFY modelUpdated)

public:
	Shape(Project* project);
	virtual ~Shape();

	virtual void reset() override;
	void copy(const Shape& shape);

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
} // namespace fsd

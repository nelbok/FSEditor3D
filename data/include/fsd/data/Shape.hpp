#pragma once

#include <fsd/data/Geometry.hpp>

namespace fsd {
class Model;

class Shape : public Geometry {
	Q_OBJECT
	Q_PROPERTY(Model* model READ model WRITE setModel NOTIFY modelUpdated)

public:
	Shape(Project* project, QObject* parent = nullptr);
	virtual ~Shape();

	virtual void reset() override;
	void copy(const Shape& shape);

	Model* model() const;
	void setModel(Model* model);

	virtual QVector3D globalPosition() const override;
	virtual QVector3D globalRotation() const override;
	virtual QVector3D globalScale() const override;

	virtual void load(const QJsonObject& json) override;
	virtual void save(QJsonObject& json) const override;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void modelUpdated();
};
} // namespace fsd

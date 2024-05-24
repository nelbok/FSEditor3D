#pragma once

#include <QtCore/QObject>
#include <QtCore/QUuid>

#include "models/EntityModel.hpp"

namespace lhe {
class SelectionManager : public QObject {
	Q_OBJECT
	Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentUpdated)
	Q_PROPERTY(lh::Entity* currentData READ currentData WRITE setCurrentData NOTIFY currentUpdated)
	Q_PROPERTY(EntityModel* model READ model WRITE setModel NOTIFY modelUpdated)

public:
	SelectionManager(QObject* parent = nullptr);
	virtual ~SelectionManager();

	int currentIndex() const;
	void setCurrentIndex(int currentIndex);

	lh::Entity* currentData() const;
	void setCurrentData(lh::Entity* currentData);

	EntityModel* model() const;
	void setModel(EntityModel* model);

private:
	QUuid _currentUuid{};
	EntityModel* _model{ nullptr };

signals:
	void currentUpdated();
	void modelUpdated();
};

} // namespace lhe

#pragma once

#include <QtCore/QObject>

#include <fsd/data/Project.hpp>

namespace fse {
class SelectionManager : public QObject {
	Q_OBJECT

	Q_PROPERTY(Type current READ current WRITE setCurrent NOTIFY currentUpdated)
	Q_PROPERTY(fsd::Link* currentLink READ currentLink WRITE setCurrentLink NOTIFY currentLinkUpdated)
	Q_PROPERTY(fsd::Model* currentModel READ currentModel WRITE setCurrentModel NOTIFY currentModelUpdated)
	Q_PROPERTY(fsd::Object* currentObject READ currentObject WRITE setCurrentObject NOTIFY currentObjectUpdated)
	Q_PROPERTY(fsd::Place* currentPlace READ currentPlace WRITE setCurrentPlace NOTIFY currentPlaceUpdated)

public:
	enum class Type {
		Project,
		Models,
		Places,
		Objects,
		Links,
		Settings,
		None,
	};
	Q_ENUM(Type)

	SelectionManager(QObject* parent = nullptr);
	virtual ~SelectionManager();

	void init(fsd::Project* project);

	Type current() const;
	void setCurrent(const Type current);

	fsd::Link* currentLink() const;
	void setCurrentLink(fsd::Link* current);

	fsd::Model* currentModel() const;
	void setCurrentModel(fsd::Model* current);

	fsd::Object* currentObject() const;
	void setCurrentObject(fsd::Object* current);

	fsd::Place* currentPlace() const;
	void setCurrentPlace(fsd::Place* current);

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void currentUpdated();
	void currentLinkUpdated();
	void currentModelUpdated();
	void currentObjectUpdated();
	void currentPlaceUpdated();
};
} // namespace fse

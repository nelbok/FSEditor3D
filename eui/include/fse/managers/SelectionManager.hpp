#pragma once

#include <QtCore/QObject>

#include <fsd/data/EntryPoint.hpp>
#include <fsd/data/Link.hpp>
#include <fsd/data/Model.hpp>
#include <fsd/data/Object.hpp>
#include <fsd/data/Place.hpp>

namespace fse {
class SelectionManager : public QObject {
	Q_OBJECT

	Q_PROPERTY(Type currentType READ currentType WRITE setCurrentType NOTIFY currentTypeUpdated)
	Q_PROPERTY(fsd::EntryPoint* currentEntryPoint READ currentEntryPoint WRITE setCurrentEntryPoint NOTIFY currentEntryPointUpdated)
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
		EntryPoints,
		Settings,
		None,
	};
	Q_ENUM(Type)

	explicit SelectionManager(QObject* parent = nullptr);
	~SelectionManager() override;

	void reset();

	Type currentType() const;
	void setCurrentType(const Type current);

	fsd::EntryPoint* currentEntryPoint() const;
	void setCurrentEntryPoint(fsd::EntryPoint* current);

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
	void currentTypeUpdated();
	void currentEntryPointUpdated();
	void currentLinkUpdated();
	void currentModelUpdated();
	void currentObjectUpdated();
	void currentPlaceUpdated();
};
} // namespace fse

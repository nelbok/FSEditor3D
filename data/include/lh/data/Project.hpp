#pragma once

#include <QtCore/QUrl>

#include <lh/data/Entity.hpp>

namespace lh {
class Place;

class Project : public Entity {
	Q_OBJECT
	Q_PROPERTY(QUrl path READ path WRITE setPath NOTIFY pathUpdated)
	Q_PROPERTY(Place* defaultPlace READ defaultPlace WRITE setDefaultPlace NOTIFY defaultPlaceUpdated)
	Q_PROPERTY(QList<Place*> places READ places WRITE setPlaces NOTIFY placesUpdated)

public:
	Project(QObject* parent = nullptr);
	virtual ~Project();

	Q_INVOKABLE virtual void reset() override;
	Q_INVOKABLE void load(const QUrl& url);
	Q_INVOKABLE void save(const QUrl& url);

	const QUrl& path() const;
	void setPath(const QUrl& path);

	Place* defaultPlace() const;
	void setDefaultPlace(Place* defaultPlace);

	// Places
	const QList<Place*>& places() const;
	void setPlaces(const QList<Place*>& places);
	Q_INVOKABLE Place* createPlace();
	Q_INVOKABLE void removePlace(Place* place);
	Q_INVOKABLE Place* duplicatePlace(Place* place);
	void cleanPlaces();

protected:
	using Entity::copy;
	using Entity::load;
	using Entity::save;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void pathUpdated();
	void defaultPlaceUpdated();
	void placesUpdated();
};
} // namespace lh

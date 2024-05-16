#pragma once

#include <QtCore/QList>
#include <QtCore/QUrl>

#include <lh/data/Entity.hpp>

namespace lh {
class Character;
class Link;
class Place;

class Project : public Entity {
	Q_OBJECT
	Q_PROPERTY(QUrl path READ path WRITE setPath NOTIFY pathUpdated)
	Q_PROPERTY(Place* defaultPlace READ defaultPlace WRITE setDefaultPlace NOTIFY defaultPlaceUpdated)
	Q_PROPERTY(QList<Character*> characters READ characters WRITE setCharacters NOTIFY charactersUpdated)
	Q_PROPERTY(QList<Link*> links READ links WRITE setLinks NOTIFY linksUpdated)
	Q_PROPERTY(QList<Place*> places READ places WRITE setPlaces NOTIFY placesUpdated)

public:
	Project(QObject* parent = nullptr);
	virtual ~Project();

	virtual void reset() override;

	const QUrl& path() const;
	void setPath(const QUrl& path);

	Place* defaultPlace() const;
	void setDefaultPlace(Place* defaultPlace);

	// Characters
	const QList<Character*>& characters() const;
	void setCharacters(const QList<Character*>& character);
	Q_INVOKABLE Character* createCharacter();
	Q_INVOKABLE void removeCharacter(Character* character);
	Q_INVOKABLE Character* duplicateCharacter(Character* character);
	void cleanCharacters();

	// Links
	const QList<Link*>& links() const;
	void setLinks(const QList<Link*>& link);
	Q_INVOKABLE Link* createLink();
	Q_INVOKABLE void removeLink(Link* link);
	Q_INVOKABLE Link* duplicateLink(Link* link);
	void cleanLinks();

	// Places
	const QList<Place*>& places() const;
	void setPlaces(const QList<Place*>& places);
	Q_INVOKABLE Place* createPlace();
	Q_INVOKABLE void removePlace(Place* place);
	Q_INVOKABLE Place* duplicatePlace(Place* place);
	void cleanPlaces();

	void load(const QUrl& url);
	virtual void load(const QJsonObject& json) override;

	void save(const QUrl& url);
	virtual void save(QJsonObject& json) const override;

private:
	using Entity::copy;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void pathUpdated();
	void defaultPlaceUpdated();
	void charactersUpdated();
	void linksUpdated();
	void placesUpdated();
};
} // namespace lh

#pragma once

#include <QtCore/QList>

#include <lh/data/Entity.hpp>

namespace lh {
class Character;
class Link;
class Model;
class Place;

class Project : public Entity {
	Q_OBJECT
	Q_PROPERTY(Place* defaultPlace READ defaultPlace WRITE setDefaultPlace NOTIFY defaultPlaceUpdated)
	Q_PROPERTY(QList<Character*> characters READ characters WRITE setCharacters NOTIFY charactersUpdated)
	Q_PROPERTY(QList<Link*> links READ links WRITE setLinks NOTIFY linksUpdated)
	Q_PROPERTY(QList<Model*> models READ models WRITE setModels NOTIFY modelsUpdated)
	Q_PROPERTY(QList<Place*> places READ places WRITE setPlaces NOTIFY placesUpdated)

public:
	Project(QObject* parent = nullptr);
	virtual ~Project();

	virtual void reset() override;

	Place* defaultPlace() const;
	void setDefaultPlace(Place* defaultPlace);

	// Characters
	const QList<Character*>& characters() const;
	void setCharacters(const QList<Character*>& character);
	Character* createCharacter();
	void removeCharacter(Character* character);
	Character* duplicateCharacter(Character* character);
	void cleanCharacters();

	// Links
	const QList<Link*>& links() const;
	void setLinks(const QList<Link*>& link);
	Link* createLink();
	void removeLink(Link* link);
	Link* duplicateLink(Link* link);
	void cleanLinks();

	// Models
	const QList<Model*>& models() const;
	void setModels(const QList<Model*>& models);
	Model* createModel();
	void removeModel(Model* model);
	Model* duplicateModel(Model* model);
	void cleanModels();

	// Places
	const QList<Place*>& places() const;
	void setPlaces(const QList<Place*>& places);
	Place* createPlace();
	void removePlace(Place* place);
	Place* duplicatePlace(Place* place);
	void cleanPlaces();

	virtual void load(const QJsonObject& json) override;
	virtual void save(QJsonObject& json) const override;

private:
	using Entity::copy;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void defaultPlaceUpdated();
	void charactersUpdated();
	void linksUpdated();
	void modelsUpdated();
	void placesUpdated();
};
} // namespace lh

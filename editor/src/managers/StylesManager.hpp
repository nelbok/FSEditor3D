#pragma once

#include <QtCore/QObject>

#include "tools/Style.hpp"

namespace fse {
class StylesManager : public QObject {
	Q_OBJECT
	Q_PROPERTY(int index READ index WRITE setIndex NOTIFY indexUpdated)
	Q_PROPERTY(const Style& current READ current NOTIFY currentUpdated)
	Q_PROPERTY(QList<Style> styles READ styles CONSTANT)

public:
	StylesManager(QObject* parent = nullptr);
	virtual ~StylesManager();

	void init();
	void createJson() const;

	int index() const;
	void setIndex(int index);

	const Style& current() const;
	const QList<Style>& styles() const;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void indexUpdated();
	void currentUpdated();
};
} // namespace fse

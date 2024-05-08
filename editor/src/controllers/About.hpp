#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>

namespace lhe {

class About : public QObject {
	Q_OBJECT
	Q_PROPERTY(QString organization READ organization CONSTANT)
	Q_PROPERTY(QString copyright READ copyright CONSTANT)
	Q_PROPERTY(QString year READ year CONSTANT)
	Q_PROPERTY(QString name READ name CONSTANT)
	Q_PROPERTY(QString version READ version CONSTANT)
	Q_PROPERTY(QString github READ github CONSTANT)
	Q_PROPERTY(QString discord READ discord CONSTANT)
	Q_PROPERTY(QString twitter READ twitter CONSTANT)

public:
	About(QObject* parent = nullptr);
	virtual ~About();

	QString organization() const;
	QString copyright() const;
	QString year() const;
	QString name() const;
	QString version() const;
	QString github() const;
	QString discord() const;
	QString twitter() const;
};
} // namespace lhe

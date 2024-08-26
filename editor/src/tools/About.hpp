#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>

namespace fse {

class About {
	Q_GADGET
	Q_PROPERTY(QString organization READ organization CONSTANT)
	Q_PROPERTY(QString copyright READ copyright CONSTANT)
	Q_PROPERTY(QString year READ year CONSTANT)
	Q_PROPERTY(QString description READ description CONSTANT)
	Q_PROPERTY(QString name READ name CONSTANT)
	Q_PROPERTY(QString version READ version CONSTANT)
	Q_PROPERTY(QString github READ github CONSTANT)
	Q_PROPERTY(QString discord READ discord CONSTANT)
	Q_PROPERTY(QString twitter READ twitter CONSTANT)

public:
	QString organization() const;
	QString copyright() const;
	QString year() const;
	QString description() const;
	QString name() const;
	QString version() const;
	QString github() const;
	QString discord() const;
	QString twitter() const;
};
} // namespace fse

#pragma once

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtCore/QUrl>
#include <QtCore/QUuid>
#include <QtCore/QString>
#include <QtGui/QColor>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>

namespace lh {

namespace Json {
// Common
QJsonValue toValue(const QString& key, const QJsonObject& json);
QJsonObject toObject(const QString& key, const QJsonObject& json);
QJsonArray toArray(const QString& key, const QJsonObject& json);
QString toString(const QString& key, const QJsonObject& json);
int toInt(const QString& key, const QJsonObject& json);
double toDouble(const QString& key, const QJsonObject& json);

// Qt classes
QUrl toUrl(const QJsonValue& json);
QJsonValue fromUrl(const QUrl& value);

QUuid toUuid(const QJsonValue& json);
QJsonValue fromUuid(const QUuid& value);

QColor toColor(const QJsonObject& json);
QJsonObject fromColor(const QColor& value);

QVector2D toVector2D(const QJsonObject& json);
QJsonObject fromVector2D(const QVector2D& value);

QVector3D toVector3D(const QJsonObject& json);
QJsonObject fromVector3D(const QVector3D& value);
}; // namespace Json

} // namespace lh

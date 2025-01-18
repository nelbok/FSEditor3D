/*
 * Copyright (c) 2024 Foxxy Soft.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution
 */

#pragma once

#include <fsd/data/FSDataExport.h>

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtCore/QUrl>
#include <QtCore/QUuid>
#include <QtCore/QString>
#include <QtGui/QColor>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>

namespace fsd {

/**
 * @brief Tools to transform data into JSon object and vice versa.
 *
 * Each functions can throw an exception if the key isn't found or it isn't possible to convert the value.
 */
namespace Json {
/** @name Common conversion
 * @{
 */

/**
 * @brief Extract a QJsonValue from the QJsonObject with the corresponding key.
 */
FSDATA_EXPORT QJsonValue toValue(const QString& objectName, const QString& key, const QJsonObject& json);
/**
 * @brief Extract a QJsonObject from the QJsonObject with the corresponding key.
 */
FSDATA_EXPORT QJsonObject toObject(const QString& objectName, const QString& key, const QJsonObject& json);
/**
 * @brief Extract a QJsonArray from the QJsonObject with the corresponding key.
 */
FSDATA_EXPORT QJsonArray toArray(const QString& objectName, const QString& key, const QJsonObject& json);
/**
 * @brief Extract a QString from the QJsonObject with the corresponding key.
 */
FSDATA_EXPORT QString toString(const QString& objectName, const QString& key, const QJsonObject& json);
/**
 * @brief Extract an int from the QJsonObject with the corresponding key.
 */
FSDATA_EXPORT int toInt(const QString& objectName, const QString& key, const QJsonObject& json);
/**
 * @brief Extract a double from the QJsonObject with the corresponding key.
 */
FSDATA_EXPORT double toDouble(const QString& objectName, const QString& key, const QJsonObject& json);
/**
 * @brief Extract a bool from the QJsonObject with the corresponding key.
 */
FSDATA_EXPORT bool toBool(const QString& objectName, const QString& key, const QJsonObject& json);
/** @} */

/** @name Qt classes conversion
 * @{
 */

/**
 * @brief Extract a QUrl from the QJsonObject with the corresponding key.
 */
FSDATA_EXPORT QUrl toUrl(const QString& objectName, const QString& key, const QJsonObject& json);
/**
 * @brief Convert a QUrl into QJsonValue.
 */
FSDATA_EXPORT QJsonValue fromUrl(const QUrl& value);

/**
 * @brief Extract a QUuid from the QJsonObject with the corresponding key.
 */
FSDATA_EXPORT QUuid toUuid(const QString& objectName, const QString& key, const QJsonObject& json);
/**
 * @brief Convert a QUuid into QJsonValue.
 */
FSDATA_EXPORT QJsonValue fromUuid(const QUuid& value);

/**
 * @brief Extract a QColor from the QJsonObject with the corresponding key.
 */
FSDATA_EXPORT QColor toColor(const QString& objectName, const QString& key, const QJsonObject& json);
/**
 * @brief Convert a QColor into QJsonValue.
 */
FSDATA_EXPORT QJsonValue fromColor(const QColor& value);

/**
 * @brief Extract a QVector2D from the QJsonObject with the corresponding key.
 */
FSDATA_EXPORT QVector2D toVector2D(const QString& objectName, const QString& key, const QJsonObject& json);
/**
 * @brief Convert a QVector2D into QJsonObject.
 */
FSDATA_EXPORT QJsonObject fromVector2D(const QVector2D& value);

/**
 * @brief Extract a QVector3D from the QJsonObject with the corresponding key.
 */
FSDATA_EXPORT QVector3D toVector3D(const QString& objectName, const QString& key, const QJsonObject& json);
/**
 * @brief Convert a QVector3D into QJsonObject.
 */
FSDATA_EXPORT QJsonObject fromVector3D(const QVector3D& value);
/** @} */
}; // namespace Json

} // namespace fsd

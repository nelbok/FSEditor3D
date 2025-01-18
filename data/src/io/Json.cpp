#include <fsd/io/Json.hpp>

#include <fsd/io/JsonException.hpp>

namespace fsd::Json {
// Common
QJsonValue toValue(const QString& objectName, const QString& key, const QJsonObject& json) {
	if (!json.contains(key)) {
		throw JsonException(objectName, key, JsonException::Error::UnknownKey);
	}
	return json[key];
}

QJsonObject toObject(const QString& objectName, const QString& key, const QJsonObject& json) {
	if (!json.contains(key) || !json[key].isObject()) {
		throw JsonException(objectName, key, JsonException::Error::InvalidObject);
	}
	return json[key].toObject();
}

QJsonArray toArray(const QString& objectName, const QString& key, const QJsonObject& json) {
	if (!json.contains(key) || !json[key].isArray()) {
		throw JsonException(objectName, key, JsonException::Error::InvalidArray);
	}
	return json[key].toArray();
}

QString toString(const QString& objectName, const QString& key, const QJsonObject& json) {
	if (!json.contains(key) || !json[key].isString()) {
		throw JsonException(objectName, key, JsonException::Error::InvalidString);
	}
	return json[key].toString();
}

int toInt(const QString& objectName, const QString& key, const QJsonObject& json) {
	if (!json.contains(key) || !json[key].isDouble()) {
		throw JsonException(objectName, key, JsonException::Error::InvalidInteger);
	}
	return json[key].toInt();
}

double toDouble(const QString& objectName, const QString& key, const QJsonObject& json) {
	if (!json.contains(key) || !json[key].isDouble()) {
		throw JsonException(objectName, key, JsonException::Error::InvalidDouble);
	}
	return json[key].toDouble();
}

bool toBool(const QString& objectName, const QString& key, const QJsonObject& json) {
	if (!json.contains(key) || !json[key].isBool()) {
		throw JsonException(objectName, key, JsonException::Error::InvalidBoolean);
	}
	return json[key].toBool();
}

// Qt classes
QUrl toUrl(const QString& objectName, const QString& key, const QJsonObject& json) {
	const auto& value = toValue(objectName, key, json);
	if (!value.toVariant().isValid()) {
		throw JsonException(objectName, key, JsonException::Error::InvalidUrl);
	}
	return value.toVariant().toUrl();
}

QJsonValue fromUrl(const QUrl& value) {
	return QJsonValue::fromVariant(value);
}

QUuid toUuid(const QString& objectName, const QString& key, const QJsonObject& json) {
	const auto& value = toValue(objectName, key, json);
	if (!value.toVariant().isValid()) {
		throw JsonException(objectName, key, JsonException::Error::InvalidUuid);
	}
	return value.toVariant().toUuid();
}

QJsonValue fromUuid(const QUuid& value) {
	return QJsonValue::fromVariant(value);
}

QColor toColor(const QString& objectName, const QString& key, const QJsonObject& json) {
	const auto& value = toValue(objectName, key, json);
	if (!value.isString()) {
		throw JsonException(objectName, key, JsonException::Error::InvalidColor);
	}
	return { value.toString() };
}

QJsonValue fromColor(const QColor& value) {
	return { value.name(QColor::HexArgb) };
}

QVector2D toVector2D(const QString& objectName, const QString& key, const QJsonObject& json) {
	const auto& object = toObject(objectName, key, json);
	const auto& name = objectName + ": " + key;
	return {
		static_cast<float>(toDouble(name, "x", object)),
		static_cast<float>(toDouble(name, "y", object)),
	};
}

QJsonObject fromVector2D(const QVector2D& value) {
	QJsonObject json;
	json["x"] = value.x();
	json["y"] = value.y();
	return json;
}

QVector3D toVector3D(const QString& objectName, const QString& key, const QJsonObject& json) {
	const auto& object = toObject(objectName, key, json);
	const auto& name = objectName + ": " + key;
	return {
		static_cast<float>(toDouble(name, "x", object)),
		static_cast<float>(toDouble(name, "y", object)),
		static_cast<float>(toDouble(name, "z", object)),
	};
}

QJsonObject fromVector3D(const QVector3D& value) {
	QJsonObject json;
	json["x"] = value.x();
	json["y"] = value.y();
	json["z"] = value.z();
	return json;
}
} // namespace fsd::Json

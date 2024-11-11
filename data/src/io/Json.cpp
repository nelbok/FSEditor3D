#include <fsd/io/Json.hpp>

#include <fsd/io/JsonException.hpp>

namespace fsd::Json {
// Common
QJsonValue toValue(const QString& key, const QJsonObject& json) {
	if (!json.contains(key)) {
		throw JsonException(JsonException::Error::UnknownKey);
	}
	return json[key];
}

QJsonObject toObject(const QString& key, const QJsonObject& json) {
	if (!json.contains(key) || !json[key].isObject()) {
		throw JsonException(JsonException::Error::InvalidObject);
	}
	return json[key].toObject();
}

QJsonArray toArray(const QString& key, const QJsonObject& json) {
	if (!json.contains(key) || !json[key].isArray()) {
		throw JsonException(JsonException::Error::InvalidArray);
	}
	return json[key].toArray();
}

QString toString(const QString& key, const QJsonObject& json) {
	if (!json.contains(key) || !json[key].isString()) {
		throw JsonException(JsonException::Error::InvalidString);
	}
	return json[key].toString();
}

int toInt(const QString& key, const QJsonObject& json) {
	if (!json.contains(key) || !json[key].isDouble()) {
		throw JsonException(JsonException::Error::InvalidInteger);
	}
	return json[key].toInt();
}

double toDouble(const QString& key, const QJsonObject& json) {
	if (!json.contains(key) || !json[key].isDouble()) {
		throw JsonException(JsonException::Error::InvalidDouble);
	}
	return json[key].toDouble();
}

bool toBool(const QString& key, const QJsonObject& json) {
	if (!json.contains(key) || !json[key].isBool()) {
		throw JsonException(JsonException::Error::InvalidBoolean);
	}
	return json[key].toBool();
}

// Qt classes
QUrl toUrl(const QJsonValue& json) {
	if (!json.toVariant().isValid()) {
		throw JsonException(JsonException::Error::InvalidUrl);
	}
	return json.toVariant().toUrl();
}

QJsonValue fromUrl(const QUrl& value) {
	return QJsonValue::fromVariant(value);
}

QUuid toUuid(const QJsonValue& json) {
	if (!json.toVariant().isValid()) {
		throw JsonException(JsonException::Error::InvalidUuid);
	}
	return json.toVariant().toUuid();
}

QJsonValue fromUuid(const QUuid& value) {
	return QJsonValue::fromVariant(value);
}

QColor toColor(const QJsonValue& json) {
	if (!json.isString()) {
		throw JsonException(JsonException::Error::InvalidColor);
	}
	return { json.toString() };
}

QJsonValue fromColor(const QColor& value) {
	return { value.name(QColor::HexArgb) };
}

QVector2D toVector2D(const QJsonObject& json) {
	return {
		static_cast<float>(toDouble("x", json)),
		static_cast<float>(toDouble("y", json)),
	};
}

QJsonObject fromVector2D(const QVector2D& value) {
	QJsonObject json;
	json["x"] = value.x();
	json["y"] = value.y();
	return json;
}

QVector3D toVector3D(const QJsonObject& json) {
	return {
		static_cast<float>(toDouble("x", json)),
		static_cast<float>(toDouble("y", json)),
		static_cast<float>(toDouble("z", json)),
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

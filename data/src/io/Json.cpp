#include <fsd/io/Json.hpp>

#include <stdexcept>

namespace fsd::Json {
// Common
QJsonValue toValue(const QString& key, const QJsonObject& json) {
	if (!json.contains(key)) {
		throw std::runtime_error("JSON doesn't contain the key");
	}
	return json[key];
}

QJsonObject toObject(const QString& key, const QJsonObject& json) {
	if (!json.contains(key) || !json[key].isObject()) {
		throw std::runtime_error("JSON doesn't contain the key or the value isn't an object");
	}
	return json[key].toObject();
}

QJsonArray toArray(const QString& key, const QJsonObject& json) {
	if (!json.contains(key) || !json[key].isArray()) {
		throw std::runtime_error("JSON doesn't contain the key or the value isn't an array");
	}
	return json[key].toArray();
}

QString toString(const QString& key, const QJsonObject& json) {
	if (!json.contains(key) || !json[key].isString()) {
		throw std::runtime_error("JSON doesn't contain the key or the value isn't a string");
	}
	return json[key].toString();
}

int toInt(const QString& key, const QJsonObject& json) {
	if (!json.contains(key) || !json[key].isDouble()) {
		throw std::runtime_error("JSON doesn't contain the key or the value isn't an integer");
	}
	return json[key].toInt();
}

double toDouble(const QString& key, const QJsonObject& json) {
	if (!json.contains(key) || !json[key].isDouble()) {
		throw std::runtime_error("JSON doesn't contain the key or the value isn't a double");
	}
	return json[key].toDouble();
}

bool toBool(const QString& key, const QJsonObject& json) {
	if (!json.contains(key) || !json[key].isBool()) {
		throw std::runtime_error("JSON doesn't contain the key or the value isn't a bool");
	}
	return json[key].toBool();
}

// Qt classes
QUrl toUrl(const QJsonValue& json) {
	if (!json.toVariant().isValid()) {
		throw std::runtime_error("JSON isn't a valid url");
	}
	return json.toVariant().toUrl();
}

QJsonValue fromUrl(const QUrl& value) {
	return QJsonValue::fromVariant(value);
}

QUuid toUuid(const QJsonValue& json) {
	if (!json.toVariant().isValid()) {
		throw std::runtime_error("JSON isn't a valid uuid");
	}
	return json.toVariant().toUuid();
}

QJsonValue fromUuid(const QUuid& value) {
	return QJsonValue::fromVariant(value);
}

QColor toColor(const QJsonValue& json) {
	if (!json.isString()) {
		throw std::runtime_error("JSON isn't a valid color");
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

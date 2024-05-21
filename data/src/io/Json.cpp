#include <lh/io/Json.hpp>

namespace lh::Json {
// Common
QJsonValue toValue(const QString& key, const QJsonObject& json) {
	assert(json.contains(key));
	return json[key];
}

QJsonObject toObject(const QString& key, const QJsonObject& json) {
	assert(json.contains(key) && json[key].isObject());
	return json[key].toObject();
}

QJsonArray toArray(const QString& key, const QJsonObject& json) {
	assert(json.contains(key) && json[key].isArray());
	return json[key].toArray();
}

QString toString(const QString& key, const QJsonObject& json) {
	assert(json.contains(key) && json[key].isString());
	return json[key].toString();
}

int toInt(const QString& key, const QJsonObject& json) {
	assert(json.contains(key) && json[key].isDouble());
	return json[key].toInt();
}

double toDouble(const QString& key, const QJsonObject& json) {
	assert(json.contains(key) && json[key].isDouble());
	return json[key].toDouble();
}

// Qt classes
QUrl toUrl(const QJsonValue& json) {
	assert(json.toVariant().isValid());
	return json.toVariant().toUrl();
}

QJsonValue fromUrl(const QUrl& value) {
	return QJsonValue::fromVariant(value);
}

QUuid toUuid(const QJsonValue& json) {
	assert(json.toVariant().isValid());
	return json.toVariant().toUuid();
}

QJsonValue fromUuid(const QUuid& value) {
	return QJsonValue::fromVariant(value);
}

QColor toColor(const QJsonObject& json) {
	return {
		toInt("r", json),
		toInt("g", json),
		toInt("b", json),
		toInt("a", json),
	};
}

QJsonObject fromColor(const QColor& value) {
	QJsonObject json;
	json["a"] = value.alpha();
	json["r"] = value.red();
	json["g"] = value.green();
	json["b"] = value.blue();
	return json;
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
} // namespace lh::Json

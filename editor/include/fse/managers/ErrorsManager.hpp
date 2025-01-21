#pragma once

#include <QtCore/QObject>

namespace fse {
class ErrorsManager : public QObject {
	Q_OBJECT
	Q_PROPERTY(QString message READ message NOTIFY typeUpdated)
	Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeUpdated)

public:
	enum class Type {
		NoError,
		BalsamError,
		FileError,
		StyleError,
		TranslatorError,
	};
	Q_ENUM(Type)

	explicit ErrorsManager(QObject* parent = nullptr);
	~ErrorsManager() override;

	QString message() const;

	Type type() const;
	void setType(Type type, const QString& message = "");

private:
	Type _type{ Type::NoError };
	QString _message{ "" };

signals:
	void typeUpdated();
};
} // namespace fse

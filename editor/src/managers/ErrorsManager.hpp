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
		FileError,
		StyleError,
	};
	Q_ENUM(Type)

	ErrorsManager(QObject* parent = nullptr);
	virtual ~ErrorsManager();

	QString message() const;

	Type type() const;
	void setType(Type type);

	private:
	Type _type{ Type::NoError };

signals:
	void typeUpdated();

};
} // namespace fse

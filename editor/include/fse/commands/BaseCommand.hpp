#pragma once

#include <QtCore/QObject>

namespace fse {

class BaseCommand : public QObject {
	Q_OBJECT

public:
	explicit BaseCommand(QObject* parent = nullptr);
	~BaseCommand() override = default;

	virtual void undo() = 0;
	virtual void redo() = 0;
	virtual void finalize();
	virtual void clean();
};
} // namespace fse

#pragma once

#include <QtCore/QObject>

namespace fse {
class BaseCommand;
class ListCommand;

class Commands : public QObject {
	Q_OBJECT

public:
	explicit Commands(QObject* parent = nullptr);
	~Commands() override = default;

	void add(BaseCommand* command);
	BaseCommand* lastCommandDone() const;

	bool canUndo() const;
	bool canRedo() const;
	void undo();
	void redo();

	void beginList();
	void endList();

	void reset();

private:
	void internalAdd(BaseCommand* command);
	void clear(QList<BaseCommand*>& commands) const;

	QList<BaseCommand*> _undoCommands{};
	QList<BaseCommand*> _redoCommands{};
	QList<ListCommand*> _list{};

signals:
	void updated();
};
} // namespace fse

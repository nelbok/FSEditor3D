#pragma once

#include <QtCore/QObject>

namespace fse {
class Manager;
class InterfaceManager : public QObject {
	Q_OBJECT
	Q_PROPERTY(bool isProgressDialogVisible READ isProgressDialogVisible NOTIFY isProgressDialogVisibleUpdated)
	Q_PROPERTY(bool isMessageDialogVisible READ isMessageDialogVisible NOTIFY isMessageDialogVisibleUpdated)
	Q_PROPERTY(bool isAskSaveDialogVisible READ isAskSaveDialogVisible NOTIFY isAskSaveDialogVisibleUpdated)
	Q_PROPERTY(bool isInterfaceEnabled READ isInterfaceEnabled NOTIFY isInterfaceEnabledUpdated)
	Q_PROPERTY(QString message READ message NOTIFY isMessageDialogVisibleUpdated)

public:
	explicit InterfaceManager(QObject* parent = nullptr);
	~InterfaceManager() override;

	void init(Manager* manager);

	bool isProgressDialogVisible() const;
	bool isMessageDialogVisible() const;
	bool isAskSaveDialogVisible() const;
	bool isInterfaceEnabled() const;
	QString message() const;

	Q_INVOKABLE void reset();
	Q_INVOKABLE void save();
	Q_INVOKABLE void load();
	Q_INVOKABLE void quit();
	Q_INVOKABLE void requestFileTransactionInterruption();
	Q_INVOKABLE void setClipboardText(const QString& text) const;
	Q_INVOKABLE void checkForUpdates();

	// Dialogs result
	Q_INVOKABLE void okClicked();
	Q_INVOKABLE void saveClicked();
	Q_INVOKABLE void discardClicked();
	Q_INVOKABLE void cancelClicked();
	Q_INVOKABLE void saveFile(const QUrl& url);
	Q_INVOKABLE void loadFile(const QUrl& url);

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;

signals:
	void isProgressDialogVisibleUpdated();
	void isMessageDialogVisibleUpdated();
	void isAskSaveDialogVisibleUpdated();
	void isInterfaceEnabledUpdated();

	void openSaveDialog();
	void openLoadDialog();
};
} // namespace fse

#pragma once

#include <QtGui/QGuiApplication>

namespace fse {

class Application : public QGuiApplication {
	Q_OBJECT

public:
	Application(int& argc, char** argv);
	virtual ~Application();

	void init();

private:
	void initApp();
	bool initParser() const;
	void initRegister() const;

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;
};
} // namespace fse

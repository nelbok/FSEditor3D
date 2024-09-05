#pragma once

#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>

#include <fse/Manager.hpp>

namespace fse::Application {
void initApp(QGuiApplication& app);
bool initParser(QGuiApplication& app, Manager& manager);
void initRegister(Manager& manager);
void initEngine(QGuiApplication& app, QQmlApplicationEngine& engine, Manager& manager);
} // namespace fse::Application

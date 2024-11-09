#pragma once

#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>

#include <fse/Manager.hpp>

namespace fse::Application {
void initApp();
bool initParser(const QGuiApplication& app, const Manager& manager);
void initRegister(Manager& manager);
void initEngine(const QGuiApplication& app, QQmlApplicationEngine& engine, const Manager& manager);
} // namespace fse::Application

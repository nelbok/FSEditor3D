#pragma once

#include <filesystem>

#include <QtCore/QString>
#include <QtCore/QUrl>

#include <fsd/data/Model.hpp>

namespace fse::Tools {
QString toPath(const QUrl& url);
std::filesystem::path projectPath(const QUrl& path);
std::filesystem::path modelPath(const QUrl& path, const fsd::Model* model);
} // namespace fse::Tools

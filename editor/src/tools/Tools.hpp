#pragma once

#include <filesystem>

#include <QtCore/QString>
#include <QtCore/QUrl>

#include <lh/data/Model.hpp>

namespace lhe::Tools {
QString toPath(const QUrl& url);
std::filesystem::path modelPath(const QUrl& projectPath, lh::Model* model);
} // namespace lhe::Tools

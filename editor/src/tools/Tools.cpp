#include <fse/tools/Tools.hpp>

#include <QtCore/QUuid>

namespace fse::Tools {
namespace detail {
std::filesystem::path projectPath(const QUrl& path) {
	auto tmp = std::filesystem::path(Tools::toPath(path).toStdString());
	if (tmp.has_filename()) {
		tmp = tmp.parent_path();
	}
	return tmp;
}
}; // namespace detail

QString toPath(const QUrl& url) {
	if (url.isLocalFile())
		return url.toLocalFile();
	else
		return url.toString();
}

std::filesystem::path projectPath(const QUrl& path) {
	return detail::projectPath(path);
}

std::filesystem::path modelPath(const QUrl& path, fsd::Model* model) {
	assert(model);
	return detail::projectPath(path) / model->uuid().toString(QUuid::WithoutBraces).split("-").at(4).toStdString();
}
} // namespace fse::Tools

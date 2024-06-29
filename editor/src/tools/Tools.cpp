#include "Tools.hpp"

#include <QtCore/QUuid>

namespace fse::Tools {
QString toPath(const QUrl& url) {
	if (url.isLocalFile())
		return url.toLocalFile();
	else
		return url.toString();
}

std::filesystem::path modelPath(const QUrl& projectPath, fsd::Model* model) {
	assert(model);

	auto tmp = std::filesystem::path(Tools::toPath(projectPath).toStdString());
	if (tmp.has_filename()) {
		tmp = tmp.parent_path();
	}
	tmp /= model->uuid().toString(QUuid::WithoutBraces).split("-").at(4).toStdString();
	return tmp;
}
} // namespace fse::Tools

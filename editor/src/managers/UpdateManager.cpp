#include <fse/managers/UpdateManager.hpp>

#include <QtCore/QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include <fse/Config.hpp>

namespace fse {
// See file for the needle
const QUrl url = QString(fse::Config::github) + "/raw/refs/heads/master/cmake/defines.cmake";
constexpr auto needle = "FS_VERSION \"";

struct UpdateManager::Impl {
	QString version{ "0.0.0" };
	Status status{ Status::None };
	QNetworkAccessManager* networkManager{ nullptr };

	void manageReply(UpdateManager* instance, QNetworkReply* reply) {
		// An error? Ignore it
		if (reply->error() != QNetworkReply::NoError) {
			status = Status::Error;
			return;
		}

		// Check if the data contains the version
		const auto data = QString(reply->readAll());
		if (!data.contains(needle)) {
			status = Status::Error;
			return;
		}

		// Update version
		version = data.split(needle)[1].split("\"")[0];
		emit instance->versionUpdated();

		// Extract versions
		const auto distant = version.split(".");
		const auto current = QCoreApplication::applicationVersion().split(".");
		if (distant.size() != 3 || current.size() != 3) {
			status = Status::Error;
			return;
		}

		// Compare versions
		const auto major = distant[0].toInt();
		const auto minor = distant[1].toInt();
		const auto patch = distant[2].toInt();
		const auto cMajor = current[0].toInt();
		const auto cMinor = current[1].toInt();
		const auto cPatch = current[2].toInt();
		if (major > cMajor || (major == cMajor && (minor > cMinor || (minor == cMinor && patch > cPatch)))) {
			emit instance->newVersionAvailable();
		}
		status = Status::Finished;
	}
};

UpdateManager::UpdateManager(QObject* parent)
	: QObject(parent)
	, _impl{ std::make_unique<Impl>() } {
	_impl->networkManager = new QNetworkAccessManager(this);
}

UpdateManager::~UpdateManager() = default;

QString UpdateManager::version() const {
	return _impl->version;
}

UpdateManager::Status UpdateManager::status() const {
	return _impl->status;
}

void UpdateManager::checkForUpdates() {
	_impl->status = Status::Processing;
	auto* reply = _impl->networkManager->get(QNetworkRequest(url));
	connect(reply, &QNetworkReply::finished, this, [this, reply] {
		_impl->manageReply(this, reply);
		reply->deleteLater();
	});
}
} // namespace fse

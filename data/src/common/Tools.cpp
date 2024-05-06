#include "Tools.hpp"

namespace lh::Tools {
QString toPath(const QUrl& url) {
	assert(url.isValid());
	if (url.isLocalFile())
		return url.toLocalFile();
	else
		return url.toString();
}
} // namespace lh::Tools

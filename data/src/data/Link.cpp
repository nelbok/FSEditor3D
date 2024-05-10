#include <lh/data/Link.hpp>

#include <lh/data/UuidPointer.hpp>
#include <lh/io/Json.hpp>

namespace lh {
struct Link::Impl {
	UuidPointer<Link>* link{ nullptr };
};

Link::Link(Project* project)
	: Placement(project)
	, _impl{ std::make_unique<Impl>() } {
	_impl->link = makeLinkPointer(project, this);
}

Link::~Link() {}

void Link::reset() {
	Placement::reset();
	setLink(nullptr);
}

void Link::copy(const Link& link) {
	Placement::copy(link);
	setLink(link.link());
}

Link* Link::link() const {
	return (_impl->link->valid()) ? _impl->link->get() : nullptr;
}

void Link::setLink(Link* link) {
	if (_impl->link->set(link)) {
		emit linkUpdated();
	}
}

constexpr auto lLink = "link";

void Link::load(const QJsonObject& json) {
	Placement::load(json);
	_impl->link->setUuid(Json::toUuid(Json::toValue(lLink, json)));
	emit linkUpdated();
}

void Link::save(QJsonObject& json) const {
	Placement::save(json);
	json[lLink] = Json::fromUuid(_impl->link->uuid());
}
} // namespace lh

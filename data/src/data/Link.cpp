#include <fsd/data/Link.hpp>

#include <fsd/data/Project.hpp>
#include <fsd/data/UuidPointer.hpp>

namespace fsd {
struct Link::Impl {
	UuidPointer<Link>* link{ nullptr };
};

Link::Link(Project* project)
	: Placement(project, project)
	, _impl{ std::make_unique<Impl>() } {
	setObjectName("Link");
	_impl->link = makeLinkPointer(project, this);
}

Link::~Link() = default;

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

Link::Type Link::type() const {
	return Type::Link;
}

void Link::load(const QJsonObject& json) {
	Placement::load(json);
	_impl->link->setUuid(Json::toUuid(objectName(), Format::lLink, json));
	emit linkUpdated();
}

void Link::save(QJsonObject& json) const {
	Placement::save(json);
	json[Format::lLink] = Json::fromUuid(_impl->link->uuid());
}
} // namespace fsd

#pragma once

#include <QtCore/QObject>

#include <lh/data/Link.hpp>

namespace lhe {
class Commands;

class LinkCommand : public QObject {
	Q_OBJECT

public:
	LinkCommand(Commands* commands);
	virtual ~LinkCommand();

	Q_INVOKABLE void setLink(lh::Link* link, lh::Link* otherlink);

protected:
	Commands* _c{ nullptr };
};
} // namespace lhe

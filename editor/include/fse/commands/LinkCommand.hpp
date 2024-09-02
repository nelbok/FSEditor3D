#pragma once

#include <QtCore/QObject>

#include <fsd/data/Link.hpp>

namespace fse {
class Commands;

class LinkCommand : public QObject {
	Q_OBJECT

public:
	LinkCommand(Commands* commands);
	virtual ~LinkCommand();

	Q_INVOKABLE void setLink(fsd::Link* link, fsd::Link* otherlink);

protected:
	Commands* _c{ nullptr };
};
} // namespace fse

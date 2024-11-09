#pragma once

#include <QtCore/QObject>

#include <fsd/data/Link.hpp>

namespace fse {
class Commands;

class LinkCommand : public QObject {
	Q_OBJECT

public:
	explicit LinkCommand(Commands* commands);
	~LinkCommand() override;

	Q_INVOKABLE void setLink(fsd::Link* link, fsd::Link* otherlink);

private:
	Commands* _c{ nullptr };
};
} // namespace fse

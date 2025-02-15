#pragma once

#include <QtCore/QObject>

// Entity macro
#define TOOLS_SETTER(CLASSNAME, MEMBER) fsd::Tools::setter(this, _impl->MEMBER, MEMBER, &CLASSNAME::MEMBER##Updated)

namespace fsd::Tools {
// Entity member
template<class TInstance, class TType>
void setter(TInstance* instance, TType& member, const TType& value, void (TInstance::*signal)()) {
	if (member != value) {
		member = value;
		emit(instance->*signal)();
	}
}
} // namespace fsd::Tools

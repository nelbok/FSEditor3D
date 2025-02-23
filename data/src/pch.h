#pragma once

#include <string>

#include <QtCore/QObject>

#include <fsd/io/Format.hpp>
#include <fsd/io/Json.hpp>

#define TOOLS_SETTER(CLASSNAME, MEMBER) fsd::Tools::setter<CLASSNAME>(this, _impl->MEMBER, MEMBER, &CLASSNAME::MEMBER##Updated)

namespace fsd {
namespace Tools {
template<class TInstance, class TType>
void setter(TInstance* instance, TType& member, const TType& value, std::function<void(TInstance*)> signalFunc) {
	if (member != value) {
		member = value;
		emit signalFunc(instance);
	}
}
} // namespace Tools

class EntryPoint;
class Link;
class Model;
class Object;
class Place;
class Project;

template<class TType>
class Container;

template<class TType>
class UuidPointer;
} // namespace fsd

Q_DECLARE_OPAQUE_POINTER(fsd::EntryPoint*)
Q_DECLARE_OPAQUE_POINTER(fsd::Link*)
Q_DECLARE_OPAQUE_POINTER(fsd::Model*)
Q_DECLARE_OPAQUE_POINTER(fsd::Object*)
Q_DECLARE_OPAQUE_POINTER(fsd::Place*)

Q_DECLARE_OPAQUE_POINTER(fsd::Container<fsd::EntryPoint>*)
Q_DECLARE_OPAQUE_POINTER(fsd::Container<fsd::Link>*)
Q_DECLARE_OPAQUE_POINTER(fsd::Container<fsd::Model>*)
Q_DECLARE_OPAQUE_POINTER(fsd::Container<fsd::Object>*)
Q_DECLARE_OPAQUE_POINTER(fsd::Container<fsd::Place>*)

Q_DECLARE_OPAQUE_POINTER(fsd::UuidPointer<fsd::EntryPoint>*)
Q_DECLARE_OPAQUE_POINTER(fsd::UuidPointer<fsd::Link>*)
Q_DECLARE_OPAQUE_POINTER(fsd::UuidPointer<fsd::Model>*)
Q_DECLARE_OPAQUE_POINTER(fsd::UuidPointer<fsd::Object>*)
Q_DECLARE_OPAQUE_POINTER(fsd::UuidPointer<fsd::Place>*)

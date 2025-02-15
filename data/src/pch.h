#pragma once

#include <QtCore/QObject>

namespace fsd {
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

#pragma once

#include <QtCore/QString>
#include <QtCore/QUrl>

// Entity macro
#define TOOLS_SETTER(CLASSNAME, MEMBER) lh::Tools::setter(this, _impl->MEMBER, MEMBER, &CLASSNAME::MEMBER##Updated)
#define TOOLS_CREATE_ENTITY(CLASSNAME, MEMBER) return lh::Tools::createEntity(this, _impl->MEMBER, &CLASSNAME::MEMBER##Updated)
#define TOOLS_REMOVE_ENTITY(CLASSNAME, VALUE) lh::Tools::removeEntity(this, _impl->VALUE##s, VALUE, &CLASSNAME::VALUE##sUpdated)
#define TOOLS_DUPLICATE_ENTITY(CLASSNAME, VALUE) return lh::Tools::duplicateEntity(this, _impl->VALUE##s, VALUE, &CLASSNAME::VALUE##sUpdated)
#define TOOLS_CLEAN_ENTITIES(CLASSNAME, MEMBER) lh::Tools::cleanEntities(this, _impl->MEMBER, &CLASSNAME::MEMBER##Updated)

namespace lh::Tools {
QString toPath(const QUrl& url);

// Entity member
template<class TInstance, class TType>
void setter(TInstance* instance, TType& member, const TType& value, void (TInstance::*signal)()) {
	if (member != value) {
		member = value;
		emit(instance->*signal)();
	}
}

// Entity List
template<class TInstance, class TType>
TType* createEntity(TInstance* instance, QList<TType*>& container, void (TInstance::*signal)()) {
	auto* entity = new TType(instance);
	entity->reset();
	container.append(entity);
	emit(instance->*signal)();
	return entity;
}

template<class TInstance, class TType>
void removeEntity(TInstance* instance, QList<TType*>& container, TType* value, void (TInstance::*signal)()) {
	assert(value);
	assert(container.contains(value));
	container.removeAll(value);
	value->deleteLater();
	emit(instance->*signal)();
}

template<class TInstance, class TType>
TType* duplicateEntity(TInstance* instance, QList<TType*>& container, TType* value, void (TInstance::*signal)()) {
	auto* entity = new TType(instance);
	entity->copy(*value);
	entity->setName(entity->name() + "*");
	container.append(entity);
	emit(instance->*signal)();
	return entity;
}

template<class TInstance, class TType>
void cleanEntities(TInstance* instance, QList<TType*>& container, void (TInstance::*signal)()) {
	for (auto* entity : container) {
		entity->reset();
		entity->deleteLater();
	}
	container.clear();
	emit(instance->*signal)();
}

} // namespace lh::Tools

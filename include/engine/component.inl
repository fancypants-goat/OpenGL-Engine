
#include "entity.h"

template<typename T>
T *engine::Component::requireComponent(T *&cached, bool includeDisabled)
{
	if (!cached)
		cached = getComponent<T>(includeDisabled);
	return cached;
}

template<typename T>
T *engine::Component::getComponent(bool includeDisabled)
{
	return entity->template getComponent<T>(includeDisabled);
}

template<typename T>
T *engine::Component::addComponent(T *component)
{
	return entity->addComponent(component);
}

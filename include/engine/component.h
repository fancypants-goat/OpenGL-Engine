//
// Created by michiel on 8/23/25.
//

#ifndef ENGINE_COMPONENT_H
#define ENGINE_COMPONENT_H


namespace engine
{
	class Entity;
	class Component
	{
	public:
		virtual void update();
		
		Entity *entity;
		bool enabled;
	};
}

#endif //ENGINE_COMPONENT_H

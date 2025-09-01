//
// Created by michiel on 8/23/25.
//

#ifndef ENGINE_COMPONENT_H
#define ENGINE_COMPONENT_H

#include <bits/stdc++.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace engine {
	class Entity;
	
	class Transform;
	
	class Component
	{
	public:
		static Component *create(const std::vector<std::string> args);
		
		virtual void update(GLFWwindow *window);
		
		template<typename T>
		T *requireComponent(T *&cached, bool includeDisabled = false);
		
		template<typename T>
		T *getComponent(bool includeDisabled = false);
		
		template<typename T>
		T *addComponent(T *component);
		
		Entity *entity {nullptr};
		Transform *transform {nullptr};
		bool enabled = true;
	};
}

#include "component.inl"
#include "component_factory.h"

#endif //ENGINE_COMPONENT_H

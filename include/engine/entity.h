//
// Created by michiel on 8/23/25.
//

#ifndef ENGINE_ENTITY_H
#define ENGINE_ENTITY_H

#include <engine/component.h>
#include <engine/transform.h>
#include <engine/mesh_renderer.h>

// Entity -> stores transform __Data__ and __Logic__
// Transform __Data__ is stored in the __Transform__ component
// __Rendering__ happens in the __Renderer__, this is NOT a component, but a __separate piece__
// __Renderer__ stores a __list__ of __Entities__
// grabbing the __Transform__ from each entity when rendering

namespace engine
{
	class Entity
	{
	public:
		explicit Entity(glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1));
		Entity(Transform transform);
		
		void update(GLFWwindow *window);
		
		template<typename T>
		T *addComponent(T *component);
		
		template<typename T>
		T *getComponent(bool includeDisabled);
		
		void setRenderer(MeshRenderer *renderer);
		
		Transform transform;
		MeshRenderer *renderer { nullptr };
		glm::vec3 color = glm::vec3(1);
		bool isActive = true;
		std::string name;
		
	private:
		std::vector<Component *> m_components;
		
		// syncing stuff
		// for the buffer swap
		friend MeshRenderer;
		friend void dataSync();
		EntityRenderData renderData;
	};
}

#include "entity.inl"

#endif // ENGINE_ENTITY_H

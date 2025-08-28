//
// Created by michiel on 8/23/25.
//

#ifndef ENGINE_GAME_OBJECT_H
#define ENGINE_GAME_OBJECT_H

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
		
		void update();
		
		template<typename T>
		T addComponent(T component)
		{
			if (!std::is_base_of<Component, T>::value)
			{
				std::cerr << typeid(T).name() << " does not inherit Component class!" << std::endl;
				return component;
			}
			
			component.entity = this;
			m_components.push_back(component);
			
			return component;
		}
		
		template<typename T>
		T getComponent(bool includeDisabled)
		{
			for (Component c : m_components)
				if (std::is_same<T, typeof(c)>::value && (includeDisabled || c.enabled))
					return (T) c;
		}
		
		void setRenderer(MeshRenderer *renderer);
		
		Transform transform;
		MeshRenderer *renderer;
		glm::vec3 color;
		
	private:
		std::vector<Component> m_components;
		
		// syncing stuff
		// for the buffer swap
		friend MeshRenderer;
		friend void dataSync();
		EntityRenderData renderData;
	};
}

#endif //ENGINE_GAME_OBJECT_H

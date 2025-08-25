//
// Created by michiel on 8/25/25.
//

#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H

#include <string>
#include "entity.h"

namespace engine {
	class Scene
	{
	public:
		Scene(std::string name);
		
		void addEntity(Entity *entity);
		
		void addDrawable(MeshRenderer *drawable);
		
		void activateScene(Scene scene);
		
		// TODO write custom .scene file type to hold data (Entities, components, data, cameras, stuff)
		Scene readFromFile(std::string source);
		
		std::string name;
		
		static Scene activeScene;
	private:
		std::vector<Entity *> m_rootEntities;
		std::vector<MeshRenderer *> m_drawables;
	};
}

#endif //ENGINE_SCENE_H

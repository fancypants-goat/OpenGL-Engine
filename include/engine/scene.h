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
		Scene() = default;
		
		Scene(std::string name);
		
		void addEntity(Entity *entity);
		
		void addDrawable(MeshRenderer *drawable);
		
		std::vector<Entity *> get_rootEntities();
		
		std::vector<MeshRenderer *> get_drawables();
		
		void activate();
		
		void drawScene(GLFWwindow *window);
		
		void updateScene(GLFWwindow *window);
		
		Entity *find(std::string &token);
		
		Entity *find(const char *token);
		
		MeshRenderer *findDrawable(std::string &token);
		
		MeshRenderer *findDrawable(const char *token);
		
		static void set_activeScene(Scene *scene);
		
		std::string name;
		
		static Scene *activeScene;
	private:
		friend void dataSync();
		
		friend class SOL;
		
		std::vector<Entity *> m_rootEntities;
		std::vector<MeshRenderer *> m_drawables;
		
		std::unordered_map<std::string, Entity *> m_tokenizedEntities;
		std::unordered_map<std::string, MeshRenderer *> m_tokenizedDrawables;
	};
}

#endif //ENGINE_SCENE_H

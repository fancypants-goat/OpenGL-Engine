//
// Created by michiel on 8/25/25.
//

#include "engine/scene.h"

namespace engine {
	
	Scene::Scene(std::string name)
	: name(name)
	, m_rootEntities(), m_drawables()
	{
	}
	
	void Scene::addEntity(Entity *entity)
	{
		m_rootEntities.push_back(entity);
	}
	
	void Scene::addDrawable(MeshRenderer *drawable)
	{
		m_drawables.push_back(drawable);
	}
	
	void Scene::activateScene(Scene scene)
	{
		activeScene = scene;
	}
}
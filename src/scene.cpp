//
// Created by michiel on 8/25/25.
//

#include "engine/scene.h"

namespace engine {
	Scene *Scene::activeScene = nullptr;
	
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
	
	void Scene::activate()
	{
		activeScene = this;
	}
	
	void Scene::set_activeScene(Scene *scene)
	{
		activeScene = scene;
	}
	
	void Scene::drawScene(GLFWwindow *window)
	{
		for (const auto& drawable : m_drawables)
		{
			drawable->upload();
			drawable->draw(window);
		}
	}
	
	void Scene::updateScene()
	{
		for (const auto& root : m_rootEntities)
		{
			root->update();
		}
	}
}
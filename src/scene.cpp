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
		std::cout << "DRAWING SCENE >>>>>>>>>>>>>>>>>" << std::endl;
		float begin = glfwGetTime();
		for (const auto& drawable : m_drawables)
		{
			float start = glfwGetTime();

			drawable->upload();
			drawable->draw(window);

			float end = glfwGetTime();
			std::cout << "Start: " << start << " End: " << end << " Time span: " << end - start << std::endl;
		}
		float final = glfwGetTime();
		std::cout << "-------------------------------------------" << std::endl;
		std::cout << "Started At: " << begin << " Ended At: " << final << " Total Span: " << final - begin << std::endl;
		std::cout << std::endl;
	}
	
	void Scene::updateScene(GLFWwindow *window)
	{
		for (const auto& root : m_rootEntities)
		{
			root->update(window);
		}
	}
	
	std::vector<Entity *> Scene::get_rootEntities()
	{
		const char *str = "hello";
		
		
		return m_rootEntities;
	}
	
	std::vector<MeshRenderer *> Scene::get_drawables()
	{
		return m_drawables;
	}
	
	Entity *Scene::find(std::string &token)
	{
		if (m_tokenizedEntities.find(token) == m_tokenizedEntities.end())
		{
			std::cerr << "Can't find entity with token " << token << std::endl;
			return nullptr;
		}
		
		return m_tokenizedEntities[token];
	}
	
	Entity *Scene::find(const char *token)
	{
		if (m_tokenizedEntities.find(token) == m_tokenizedEntities.end())
		{
			std::cerr << "Can't find entity with token " << token << std::endl;
			return nullptr;
		}
		
		return m_tokenizedEntities[token];
	}
	
	MeshRenderer *Scene::findDrawable(std::string &token)
	{
		if (m_tokenizedDrawables.find(token) == m_tokenizedDrawables.end())
		{
			std::cerr << "Can't find drawable with token " << token << std::endl;
			return nullptr;
		}
		
		return m_tokenizedDrawables[token];
	}
	
	MeshRenderer *Scene::findDrawable(const char *token)
	{
		if (m_tokenizedDrawables.find(token) == m_tokenizedDrawables.end())
		{
			std::cerr << "Can't find drawable with token " << token << std::endl;
			return nullptr;
		}
		
		return m_tokenizedDrawables[token];
	}
}
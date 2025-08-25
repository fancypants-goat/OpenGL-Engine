//
// Created by michiel on 8/23/25.
//

#include <engine/entity.h>

#include <iostream>
#include <engine/mesh_renderer.h>

namespace engine
{
	std::vector<Entity *> Entity::entities = {};
	
	Entity::Entity(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
		: transform(position, rotation, scale), renderer(nullptr)
	{
	}
	
	Entity::Entity(Transform transform)
		: transform(transform), renderer(nullptr)
	{
	}
	
	void Entity::setRenderer(MeshRenderer *newRenderer)
	{
		renderer = newRenderer;
		newRenderer->addEntitySilent(this);
	}
	
	void Entity::update()
	{
		for ()
	}
}
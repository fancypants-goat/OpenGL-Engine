//
// Created by michiel on 8/23/25.
//

#include "engine/component.h"

void engine::Component::update(GLFWwindow *window)
{
}

engine::Component *engine::Component::create(const std::vector<std::string> args)
{
	return new Component();
}

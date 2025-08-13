//
// Created by michiel on 8/13/25.
//

#include "input.h"

#include <iostream>

namespace engine {
	std::unordered_map<int, KeyState> Input::keyStates {};
	
	KeyState Input::GetKeyState(int key)
	{
		if (keyStates.find(key) != keyStates.end())
			return keyStates[key];
		
		return KeyState::UNKNOWN;
	}
	
	void Input::updateKeys(GLFWwindow *window)
	{
		for (auto &[key, state] : keyStates)
		{
			int glfwState = glfwGetKey(window, key);
			
			if (glfwState == GLFW_PRESS)
			{
				if (state == KeyState::PRESS || state == KeyState::HOLD)
					state = KeyState::HOLD;
				else
					state = KeyState::PRESS;
			} else if (glfwState == GLFW_RELEASE)
			{
				if (state == KeyState::RELEASE || state == KeyState::OFF || state == KeyState::UNKNOWN)
					state = KeyState::OFF;
				else
					state = KeyState::RELEASE;
			} else
				state = KeyState::UNKNOWN;
		}
	}
	
	void Input::initialize(GLFWwindow *window)
	{
		int lowest_key_enum (GLFW_KEY_SPACE);
		int highest_key_enum (GLFW_KEY_LAST);
		for (int k = lowest_key_enum; k <= highest_key_enum; k++)
		{
			keyStates[k] = KeyState::UNKNOWN;
		}
		updateKeys(window);
	}
} // engine
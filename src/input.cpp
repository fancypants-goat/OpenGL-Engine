//
// Created by michiel on 8/13/25.
//

#include <engine/input.h>

namespace engine {
	std::unordered_map<int, KeyState> Input::polledStates {};
	
	
	KeyState Input::getKeyState(GLFWwindow *window, int key)
	{
		int glfwState = glfwGetKey(window, key);
		
		KeyState state = KeyState::Unknown;
		
		if (polledStates.find(key) != polledStates.end())
			state = polledStates[key];
		
		if (glfwState == GLFW_PRESS) // if the button is down
		{
			if (state == KeyState::Press || state == KeyState::Hold)
				state = KeyState::Hold;
			else
				state = KeyState::Press;
		} else if (glfwState == GLFW_RELEASE)
		{
			if (state == KeyState::Release || state == KeyState::Off)
				state = KeyState::Off;
			else
				state = KeyState::Release;
		} else
			return KeyState::Unknown;
		
		// save the state into the polledStates map for later usage
		polledStates[key] = state;
		return state;
	}
} // engine
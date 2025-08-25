//
// Created by michiel on 8/13/25.
//

#include <engine/input.h>

namespace engine {
	std::unordered_map<int, KeyState> Input::keyStates {};
	std::mutex Input::inputMutex;
	
	KeyState Input::getKeyState(GLFWwindow *window, int key)
	{
		int buttonState = glfwGetKey(window, key);
		
		KeyState state = KeyState::Unknown;
		
		std::unique_lock<std::mutex> lock(inputMutex);
		
		if (keyStates.find(key) != keyStates.end())
			state = keyStates[key];
		
		if (buttonState == GLFW_PRESS) // if the button is down
		{
			if (state == KeyState::Press || state == KeyState::Hold)
				state = KeyState::Hold;
			else
				state = KeyState::Press;
		} else if (buttonState == GLFW_RELEASE)
		{
			if (state == KeyState::Release || state == KeyState::Off)
				state = KeyState::Off;
			else
				state = KeyState::Release;
		} else
			return KeyState::Unknown;
		
		keyStates[key] = state;
		return state;
	}
} // engine
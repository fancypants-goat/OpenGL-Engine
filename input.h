//
// Created by michiel on 8/13/25.
//

#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H

#include <GLFW/glfw3.h>
#include <unordered_map>

namespace engine {
	
	enum class KeyState
	{
		UNKNOWN,
		OFF,
		RELEASE,
		PRESS,
		HOLD
	};
	
	class Input
	{
	public:
		Input() = delete;
		
		static KeyState GetKeyState(int key);
		
		static void updateKeys(GLFWwindow *window);
		static void initialize(GLFWwindow *window);
	
	private:
		static std::unordered_map<int, KeyState> keyStates;
	};
	
	
} // engine

#endif //ENGINE_INPUT_H

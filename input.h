//
// Created by michiel on 8/13/25.
//

#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H

#include <GLFW/glfw3.h>
#include <unordered_map>
#include <glm/glm.hpp>

#include "mouse.h"

namespace engine {
	
	enum class KeyState
	{
		Unknown = -1,
		Off,
		Release,
		Press,
		Hold
	};
	
	class Input
	{
	public:
		Input() = delete; // static class
		
		// key states
		static KeyState getKeyState(GLFWwindow *window, int key);
	
	
	private:
		static std::unordered_map<int, KeyState> polledStates;
	};
	
	
} // engine

#endif //ENGINE_INPUT_H

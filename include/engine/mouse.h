//
// Created by michiel on 8/14/25.
//

#ifndef ENGINE_MOUSE_H
#define ENGINE_MOUSE_H

#include <unordered_map>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <shared_mutex>

namespace engine {
	
	enum class ButtonState
	{
		Unknown = -1,
		Off,
		Release,
		Press,
		Hold,
		Double,
	};
	
	enum class CursorState
	{
		Normal = GLFW_CURSOR_NORMAL,
		Hidden = GLFW_CURSOR_HIDDEN,
		Disabled = GLFW_CURSOR_DISABLED
	};
	
	class Mouse
	{
	public:
		Mouse() = delete; // static class
		
		static ButtonState getButtonState(GLFWwindow *window, int button);
		
		static glm::vec2 getMousePosition();
		static glm::vec2 getMouseOffset();
		
		static void setCursorMode(GLFWwindow *window, CursorState mode);
		static CursorState getCursorMode(GLFWwindow *window);
	
	private:
		static std::unordered_map<int, ButtonState> buttonStates;
		static glm::vec2 lastCursorPosition;
		static glm::vec2 cursorOffset;
		
		friend void glfwInputUpdateHandler(GLFWwindow *window);
		static void updateCursorPosition(GLFWwindow *window);
	};
	
} // engine

#endif //ENGINE_MOUSE_H

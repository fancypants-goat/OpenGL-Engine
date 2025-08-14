//
// Created by michiel on 8/14/25.
//

#ifndef ENGINE_MOUSE_H
#define ENGINE_MOUSE_H

#include <unordered_map>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

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
		
		static glm::vec2 getMousePosition(GLFWwindow *window);
		static glm::vec2 getMouseOffset(GLFWwindow *window);
		
		static void setCursorMode(GLFWwindow *window, CursorState mode);
		static CursorState getCursorMode(GLFWwindow *window);
		
		static void mouse_move_callback(GLFWwindow *window);
	
	private:
		static std::unordered_map<int, ButtonState> polledStates;
		static glm::vec2 lastCursorPosition;
		static glm::vec2 cursorOffset;
	};
	
} // engine

#endif //ENGINE_MOUSE_H

//
// Created by michiel on 8/14/25.
//
#include <engine/mouse.h>


namespace engine {
	std::unordered_map<int, ButtonState> Mouse::polledStates {};
	glm::vec2 Mouse::lastCursorPosition(0);
	glm::vec2 Mouse::cursorOffset(0);
	
	
	ButtonState Mouse::getButtonState(GLFWwindow *window, int button)
	{
		int glfwState = glfwGetMouseButton(window, button);
		
		ButtonState state = ButtonState::Unknown;
		
		if (polledStates.find(button) != polledStates.end())
			state = polledStates[button];
		
		if (glfwState == GLFW_PRESS)
		{
			if (state == ButtonState::Press || state == ButtonState::Hold)
				state = ButtonState::Hold;
			else
				state = ButtonState::Press;
		} else if (glfwState == GLFW_RELEASE)
		{
			if (state == ButtonState::Release || state == ButtonState::Off)
				state = ButtonState::Off;
			else
				state = ButtonState::Release;
		} else
			return ButtonState::Unknown;
		
		polledStates[button] = state;
		return state;
	}
	
	glm::vec2 Mouse::getMousePosition(GLFWwindow *window)
	{
		glm::dvec2 pos;
		glfwGetCursorPos(window, &pos.x, &pos.y);
		return pos;
	}
	
	glm::vec2 Mouse::getMouseOffset(GLFWwindow *window)
	{
		return cursorOffset;
	}
	
	void Mouse::setCursorMode(GLFWwindow *window, CursorState mode)
	{
		glfwSetInputMode(window, GLFW_CURSOR, (int) mode);
	}
	
	CursorState Mouse::getCursorMode(GLFWwindow *window)
	{
		return (CursorState) glfwGetInputMode(window, GLFW_CURSOR);
	}
	
	void Mouse::mouse_move_callback(GLFWwindow *window)
	{
		glm::vec2 newPosition = getMousePosition(window);
		cursorOffset = newPosition - lastCursorPosition;
		lastCursorPosition = newPosition; // reset the last position to that of this frame
	}
	
} // engine
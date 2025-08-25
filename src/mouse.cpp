//
// Created by michiel on 8/14/25.
//
#include <engine/mouse.h>
#include <mutex>

namespace engine {
	std::unordered_map<int, ButtonState> Mouse::buttonStates {};
	glm::vec2 Mouse::lastCursorPosition(0);
	glm::vec2 Mouse::cursorOffset(0);
	
	
	ButtonState Mouse::getButtonState(GLFWwindow *window, int button)
	{
		int glfwState = glfwGetMouseButton(window, button);
		ButtonState state = ButtonState::Unknown;
		
		if (buttonStates.find(button) != buttonStates.end())
			state = buttonStates[button];
		
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
		
		buttonStates[button] = state;
		return state;
	}
	
	glm::vec2 Mouse::getMousePosition()
	{
		return lastCursorPosition;
	}
	
	glm::vec2 Mouse::getMouseOffset()
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
	
	void Mouse::updateCursorPosition(GLFWwindow *window)
	{
		glm::dvec2 newPosition;
		glfwGetCursorPos(window, &newPosition.x, &newPosition.y);
		cursorOffset = glm::vec2(newPosition) - lastCursorPosition;
		lastCursorPosition = glm::vec2(newPosition);
	}
} // engine
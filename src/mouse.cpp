//
// Created by michiel on 8/14/25.
//
#include <engine/mouse.h>
#include <mutex>

namespace engine {
	std::unordered_map<int, ButtonState> Mouse::buttonStates {};
	math::vec2 Mouse::lastCursorPosition(0);
	math::vec2 Mouse::cursorOffset(0);
	
	
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
	
	math::vec2 Mouse::getMousePosition()
	{
		return lastCursorPosition;
	}
	
	math::vec2 Mouse::getMouseOffset()
	{
		return cursorOffset;
	}
	
	void Mouse::setCursorMode(GLFWwindow *window, CursorState mode)
	{
		glfwSetInputMode(window, GLFW_CURSOR, static_cast<int>(mode));
	}
	
	CursorState Mouse::getCursorMode(GLFWwindow *window)
	{
		return static_cast<CursorState>(glfwGetInputMode(window, GLFW_CURSOR));
	}
	
	void Mouse::updateCursorPosition(GLFWwindow *window)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		math::vec2 newPos (x, y);
		cursorOffset = math::vec2(newPos) - lastCursorPosition;
		lastCursorPosition = math::vec2(newPos);
	}
} // engine
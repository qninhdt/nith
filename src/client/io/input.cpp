#include "client/io/input.hpp"

namespace nith::io
{
	Window* Input::s_currentWindow = nullptr;
	InputEventDispatcher Input::s_eventDispatcher;

	void Input::SetCurrentWindow(Window* window)
	{
		s_currentWindow = window;
		GLFWwindow* nativeWindow = window->getNativeWindow();
	
		glfwSetCursorPosCallback(nativeWindow,
			[](GLFWwindow* _nativeWindow, double mouseX, double mouseY)
			{
				static double lastX = 0, lastY = 0;
				MouseMovedEvent event((f32)mouseX, (f32)mouseY, (f32)mouseX-lastX, (f32)mouseY-lastY);
				s_eventDispatcher.dispatchEvent(event);
			}
		);

		glfwSetKeyCallback(nativeWindow,
			[](GLFWwindow* _nativeWindow, int key, int scancode, int action, int mods)
			{
				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event((KeyCode) key, false);
					s_eventDispatcher.dispatchEvent(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event((KeyCode) key);
					s_eventDispatcher.dispatchEvent(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event((KeyCode) key, true);
					s_eventDispatcher.dispatchEvent(event);
					break;
				}
				}
			}
		);
	}
}

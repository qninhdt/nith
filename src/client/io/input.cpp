#include "client/io/input.hpp"

namespace nith::io
{
	Window* Input::s_currentWindow = nullptr;
	InputEventDispatcher Input::s_eventDispatcher;

	void Input::SetCurrentWindow(Window* window)
	{
		s_currentWindow = window;
		GLFWwindow* nativeWindow = window->getNativeWindow();
	
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

#pragma once

#include "client/window.hpp"
#include "client/io/input_event.hpp"

namespace nith::io
{
    class Input
    {
    public:

		static InputEventDispatcher& GetEventDispatcher() { return s_eventDispatcher; }

        static bool IsKeyPressed(const KeyCode& keyCode)
		{
			return glfwGetKey(s_currentWindow->getNativeWindow(), (int)keyCode) == GLFW_PRESS;
		}

        static bool IsMouseButtonPressed(const MouseButton& mouseButton)
		{
			return glfwGetMouseButton(s_currentWindow->getNativeWindow(), (int)mouseButton) == GLFW_PRESS;
		}

		static void SetCurrentWindow(Window* window);
		
		static v2 GetMousePosition()
		{
			double xPos, yPos;
			glfwGetCursorPos(s_currentWindow->getNativeWindow(), &xPos, &yPos);
			return { (f32)xPos, (f32)yPos };
		}

		static f32 GetMouseX() { return GetMousePosition().x; }

		static f32 GetMouseY() { return GetMousePosition().y; }

    private:
        static Window* s_currentWindow;
		static InputEventDispatcher s_eventDispatcher;
		static double s_lastX;
		static double s_lastY;
    };
}
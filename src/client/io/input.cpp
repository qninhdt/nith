#include "client/io/input.hpp"

namespace nith::io
{
	Window* Input::s_currentWindow = nullptr;

	void Input::SetCurrentWindow(Window* window)
	{
		s_currentWindow = window;
	}
}

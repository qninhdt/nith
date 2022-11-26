#include "client/application.hpp"

namespace nith
{
    Application::Application():
        m_mainWindow("Lktjjjflmyyfjao ysjhit", 800, 600)
    {
        init_everything();
        m_mainWindow.open();
    }

    void Application::init_everything()
    {
        // init logging
        Log::Init();

        // init GLFW
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef NITH_DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    #endif

        NITH_CLIENT_TRACE("Initialize glfw successfully");

        m_mainWindow.addEventListener<WindowClosedEvent>(
            [](const WindowClosedEvent& event)
            {
                std::cout << event << '\n';
            }
        );

        m_mainWindow.addEventListener<WindowResizedEvent>(
            [](const WindowResizedEvent& event)
            {
                std::cout << event << '\n';
            }
        );
    }

    void Application::mainLoop()
    {
        m_mainWindow.makeCurrent();

        while (m_mainWindow.isOpen())
        {
            m_mainWindow.beginLoop();
            m_mainWindow.endLoop();
        }
    }

    Application::~Application()
    {
        glfwTerminate();
    }
}
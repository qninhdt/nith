#pragma once

#include "client/window.hpp"

namespace nith
{
    class Application
    {
    public:
       
        Application();
        ~Application();

        void mainLoop();

        Window& getMainWindow();

    private:
        void init_everything();

        Window m_mainWindow;
    };

    inline Window& Application::getMainWindow()
    {
        return m_mainWindow;
    }
}
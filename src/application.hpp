#pragma once

#include "window.hpp"

namespace nith
{
    class Application
    {
    public:
       
        Application();
        ~Application();

        void mainLoop();

        Window& getMainWindow() { return m_mainWindow; }

        static const f32& GetDeltaTime() { return s_deltaTime; }

    private:
        static f32 s_deltaTime;

        void init_everything();

        Window m_mainWindow;
        
    };
}
#pragma once

#include "client/window.hpp"
#include "client/camera_controller.hpp"

namespace nith
{
    class Application
    {
    public:
       
        Application();
        ~Application();

        void mainLoop();

        Window& getMainWindow();

        static const f32& GetDeltaTime() { return s_deltaTime; }

    private:
        static f32 s_deltaTime;

        void init_everything();

        Window m_mainWindow;
        CameraController m_cameraController;
    };

    inline Window& Application::getMainWindow()
    {
        return m_mainWindow;
    }
}
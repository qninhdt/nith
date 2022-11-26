#pragma once

#include "common.hpp"
#include "client/window_event.hpp"

namespace nith
{
    class Window: public WindowEventDispatcher
    {
    public:
        Window(const std::string& title, const u32& width, const u32& height);
        ~Window();

        /// @brief Get window width
        /// 
        /// @return Window width
        u32 getWidth() const;

        /// @brief Get window height
        /// 
        /// @return Window height
        u32 getHeight() const;

        /// @brief Get window title
        /// 
        /// @return Window title
        std::string getTitle() const;

        bool isVSync() const;

        bool isOpen() const;

        GLFWwindow* getNativeWindow() const;

        void setTitle(const std::string& title);

        void setVSync(const bool& enable);
        
        /// @brief Set clear color
        /// 
        /// @param color Clear color 
        void setClearColor(const v4& color);

        /// @brief Create GLFW window.
        ///
        /// This method must be called first.
        void open();

        /// @brief Clear window screen
        void beginLoop();

        /// @brief Update window screen and close window if nessesary.
        /// 
        /// This method must be run in the end of loop.
        void endLoop();

        /// @brief Mark window to be destroy in endLoop() method.
        /// 
        /// We should use this method instead of closeImmediately()
        /// to avoid unexpected bugs in while loop.
        void close();

        /// @brief Destroy window and its states immediately and
        ///        set m_nativeWindow to nullptr.
        /// 
        /// May cause bugs.
        void closeImmediately();

        /// @brief set current window to this window.
        void makeCurrent() const;

    private:

        static void resize_handle(GLFWwindow* nativeWindow, int width, int height);
        static void input_handle();

        GLFWwindow* m_nativeWindow;
        u32 m_width;
        u32 m_height;
        bool m_vSync;
        bool m_open;
        std::string m_title;
        v4 m_clearColor;
    };

    inline GLFWwindow* Window::getNativeWindow() const
    {
        return m_nativeWindow;
    }

    inline u32 Window::getWidth() const
    {
        return m_width;
    }

    inline u32 Window::getHeight() const
    {
        return m_height;
    }

    inline std::string Window::getTitle() const
    {
        return m_title;
    }

    inline bool Window::isVSync() const
    {
        return m_vSync;
    }

    inline bool Window::isOpen() const
    {
        return m_open;
    }

    inline void Window::makeCurrent() const
    {
        glfwMakeContextCurrent(m_nativeWindow);
    }
    
}
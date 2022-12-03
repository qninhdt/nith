#include "window.hpp"

namespace nith
{
    Window::Window(const std::string& title, const u32& width,
        const u32& height) :
        m_title(title),
        m_width(width),
        m_height(height),
        m_open(false),
        m_vSync(false),
        m_showCursor(true),
        m_nativeWindow(nullptr),
        m_clearColor(1, 1, 1, 1)
    {

    }

    void Window::setTitle(const std::string& title)
    {
        m_title = title;
        glfwSetWindowTitle(m_nativeWindow, title.c_str());
    }

    void Window::setClearColor(const v4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
        m_clearColor = color;
    }

    void Window::setVSync(const bool& enabled)
    {
        if (enabled)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }
        m_vSync = enabled;
    }

    void Window::beginLoop()
    {
        makeCurrent();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::endLoop()
    {
        glfwSwapBuffers(m_nativeWindow);
        glfwPollEvents();

        if (!m_open || glfwWindowShouldClose(m_nativeWindow))
        {
            closeImmediately();
        }
    }

    void Window::toggleCursor()
    {
        if (m_showCursor)
        {
            glfwSetInputMode(m_nativeWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else
        {
            glfwSetInputMode(m_nativeWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }

        m_showCursor = !m_showCursor;
    }

    void Window::open()
    {
        m_open = true;
        m_nativeWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(),
            nullptr, nullptr);

        if (m_nativeWindow == nullptr)
        {
            NITH_CLIENT_ERROR("Cannot create window");
            return;
        }
        else
        {
            NITH_CLIENT_INFO("Open window \"{0}\": {1} x {2}", m_title, m_width, m_height);
        }


        // init glad
        makeCurrent();
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        setClearColor(m_clearColor);
        setVSync(m_vSync);

        glfwSetWindowUserPointer(m_nativeWindow, this);

        // setup callbacks
        glfwSetWindowSizeCallback(m_nativeWindow, &Window::resize_handle);
    }

    void Window::close()
    {
        m_open = false;
    }

    void Window::resize_handle(GLFWwindow* nativeWindow, int width, int height)
    {
        Window& window = *(Window*)glfwGetWindowUserPointer(nativeWindow);
        window.m_width = width;
        window.m_height = height;

        glViewport(0, 0, width, height);

        window.dispatchEvent<WindowResizedEvent>({ window, (u32) width, (u32) height });
    }

    void Window::input_handle()
    {

    }

    void Window::closeImmediately()
    {
        dispatchEvent<WindowClosedEvent>({ *this });

        glfwDestroyWindow(m_nativeWindow);

        m_open = false;
        m_nativeWindow = nullptr;
    }

    void Window::center()
    {
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        i32 posX = mode->width / 2 - m_width / 2;
        i32 posY = mode->height / 2 - m_height / 2;
        glfwSetWindowPos(m_nativeWindow, posX, posY);
    }

    Window::~Window()
    {
        if (m_open)
        {
            closeImmediately();
        }
    }
}
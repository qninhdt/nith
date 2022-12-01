#include "client/application.hpp"
#include "client/camera_controller.hpp"

// TODO: remove later
#include "client/gl/vertex_array.hpp"
#include "client/gl/shader.hpp"
#include "client/perspective_camera.hpp"
#include "client/io/input.hpp"
#include "client/io/input_event.hpp"

namespace nith
{
    float Application::s_deltaTime = 1.0f / 60;

    Application::Application():
        m_mainWindow("lmao gay", 800, 600),
        m_cameraController(10, 0.005)
    {
        init_everything();

        m_mainWindow.open();
        m_mainWindow.setClearColor({ 0, 0, 0, 1 });

        io::Input::SetCurrentWindow(&m_mainWindow);

        io::Input::GetEventDispatcher()
            .addEventListener<io::KeyPressedEvent>(
            [&](const io::KeyPressedEvent& event)
            {
                if (event.getKeyCode() == io::KeyCode::Escape)
                {
                    m_mainWindow.close();
                }
            }
        );   
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
    }

    void Application::mainLoop()
    {
        m_mainWindow.makeCurrent();

        gl::Shader shader("basic_shader");

        shader.loadFromFile("D:/github/nith/assets/shaders/basic_material.vert",
            "D:/github/nith/assets/shaders/basic_material.frag");

        gl::VertexArray vao;
        gl::VertexBuffer vbo;
        gl::IndexBuffer ebo(gl::GLDataType::Uint);

        u32 indices[] = { 0, 1, 2, 0, 2, 3  };
        f32 vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.25f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.25f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.25f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.25f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.25f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.25f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.5f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.5f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.5f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,

             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.75f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.75f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.75f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.75f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.75f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.75f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.8f,
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.8f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.8f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.8f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.8f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.8f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        };

        std::vector<f32> shit(vertices, vertices + 216);
        shit.resize(1024 * 1024);
 
        vbo.setUsage(gl::BufferUsageType::DynamicDraw);
        vbo.setData(shit);

        ebo.setData(indices, sizeof(indices));

        //vao.setIndex(ebo);
        vao.setDrawCount(6 * 6);
        vao.setBuffer(vbo, {
            { gl::GLDataType::Vec3 },
            { gl::GLDataType::Vec3 }
        });

        PerspectiveCamera camera(glm::radians(50.0f), m_mainWindow.getAspect(), 0.2, 2000);
        camera.setPosition({ 0, 0, 10 });
        camera.updateViewMatrix();

        m_mainWindow.addEventListener<WindowResizedEvent>(
            [&](const WindowResizedEvent& event)
            {
                camera.setAspect(1.0f * event.getWidth() / event.getHeight());
                camera.updateProjectionMatrix();
            }
        );

        m_cameraController.connect(&camera);

        glEnable(GL_DEPTH_TEST);

        auto lastTime = std::chrono::steady_clock::now();

        while (m_mainWindow.isOpen())
        {
            // input
            m_cameraController.update();

            // render
            m_mainWindow.beginLoop();

            shader.use();
            
            shader.setMat4(shader.getUniformLocation("model"),
                glm::translate(glm::mat4(1.0f), { 1, 0, 0 }));

            shader.setMat4(shader.getUniformLocation("projection_view"),
                camera.getProjectionViewMaxtrix());

            vao.draw();
            m_mainWindow.endLoop();

            // compute deltaTime
            auto currentTime = std::chrono::steady_clock::now();
            s_deltaTime = (currentTime - lastTime).count()/1000000000.0f;
            lastTime = currentTime;
        }
    }

    Application::~Application()
    {
        glfwTerminate();
    }
}
#include "application.hpp"

// TODO: remove later
#include "gl/vertex_array.hpp"
#include "gl/shader.hpp"
#include "io/input.hpp"
#include "io/input_event.hpp"
#include "systems/camera_system.hpp"

namespace nith
{
    float Application::s_deltaTime = 1.0f / 60;

    Application::Application():
        m_mainWindow("lmao gay", 800, 600)
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

        CameraSystem::Init(m_registry);
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

        auto camera = CameraSystem::CreateCamera(m_registry, m_mainWindow,
            1.0f * m_mainWindow.getWidth() / m_mainWindow.getHeight(), glm::radians(50.0f), 0.02, 2000);

        m_registry.get<Transform>(camera).position.z += 5;
        m_registry.get<Camera>(camera).updateViewMatrix(
            m_registry.get<Transform>(camera)
        );

        glEnable(GL_DEPTH_TEST);

        auto lastTime = std::chrono::steady_clock::now();

        while (m_mainWindow.isOpen())
        {
            // input
            CameraSystem::Update(m_registry, s_deltaTime);

            // render
            m_mainWindow.beginLoop();

            shader.use();
            
            shader.setMat4(shader.getUniformLocation("model"),
                glm::translate(glm::mat4(1.0f), { 1, 0, 0 }));

            shader.setMat4(shader.getUniformLocation("projection"),
                m_registry.get<Camera>(camera).projectionMatrix);

            shader.setMat4(shader.getUniformLocation("view"),
                m_registry.get<Camera>(camera).viewMatrix);

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
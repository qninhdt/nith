#include "client/application.hpp"

// TODO: remove later
#include "client/gl/vertex_array.hpp"
#include "client/gl/shader.hpp"
#include "client/renderer/perspective_camera.hpp"
#include "client/io/input.hpp"
#include "client/io/input_event.hpp"

namespace nith
{
    Application::Application():
        m_mainWindow("lmao gay", 800, 600)
    {
        init_everything();
        m_mainWindow.open();

        io::Input::SetCurrentWindow(&m_mainWindow);

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

        io::Input::GetEventDispatcher()
            .addEventListener<io::KeyReleasedEvent>(
            [](const io::KeyReleasedEvent& event)
            {
                std::cout << event << '\n';
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
        gl::VertexBuffer vbo1, vbo2;
        gl::IndexBuffer ebo(gl::BufferDataType::Uint);

        vao.create();
        vbo1.create();
        vbo2.create();
        ebo.create();

        u32 indices[] = { 0, 1, 2, 0, 2, 3,  };
        f32 vertices[] = {
            0.5f,  0.5f, 0.0f, 
             0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
        };
        f32 color[] = {
            1.0f, 1.0f, 1.0f,
             0.0f, 0.0f, 0.0f,
             0.0f, 0.0f, 0.0f,
             0.0f, 0.0f, 0.0f,
        };

        vbo1.bind();
        vbo1.setData(vertices, sizeof(vertices));

        vbo2.bind();
        vbo2.setData(color, sizeof(color));
        
        ebo.bind();
        ebo.setData(indices, sizeof(indices));

        vao.bind();

        std::vector<gl::BufferElement> elms;

        elms.push_back(gl::BufferElement{
            .dataType = gl::BufferDataType::Vec3,
            .normalized = false,
        });

        vao.addBuffer(vbo1, {
            .stride = 3 * 4,
            .elements = elms,
        });

        vao.addBuffer(vbo2, {
            .stride = 3 * 4,
            .elements = elms,
            });

        vao.setIndex(&ebo);

        vao.setDrawCount(6);

        PerspectiveCamera camera(glm::radians(50.0f), m_mainWindow.getAspect(), 0.2, 2000);
        camera.setPosition({ 0, 0, 10 });
        camera.updateProjectionViewMatrix();


        io::Input::GetEventDispatcher().addEventListener<io::MouseMovedEvent>(
           [&](const io::MouseMovedEvent& event)
           {
               double pitch = camera.getPitch();
               double yaw = camera.getYaw();
               double deltaX = event.getMouseDeltaX();
               double deltaY = event.getMouseDeltaY();

               yaw += deltaX/1000;
               pitch -= deltaY/1000;

               camera.setOrientation(pitch, yaw);
               camera.updateViewMatrix();
           }
        );


        while (m_mainWindow.isOpen())
        {
            m_mainWindow.beginLoop();

            shader.use();
            
            v3 position = camera.getPostion();

            if (io::Input::IsKeyPressed(io::KeyCode::A))
            {
                position.x -= 0.001;
            }
            if (io::Input::IsKeyPressed(io::KeyCode::D))
            {
                position.x += 0.001;
            }
            if (io::Input::IsKeyPressed(io::KeyCode::W))
            {
                position.z -= 0.001;
            }
            if (io::Input::IsKeyPressed(io::KeyCode::S))
            {
                position.z += 0.001;
            }

            camera.setPosition(position);
            camera.updateViewMatrix();
            shader.setMat4(shader.getUniformLocation("model"),
                glm::translate(glm::mat4(1.0f), { 1, 0, 0 }));

            shader.setMat4(shader.getUniformLocation("projection_view"),
                camera.getProjectionViewMaxtrix());

            vao.draw();
            m_mainWindow.endLoop();
        }
    }

    Application::~Application()
    {
        glfwTerminate();
    }
}
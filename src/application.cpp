#include "application.hpp"
#include "loaders/shader_loader.hpp"
#include "registry.hpp"

// TODO: remove later
#include "gl/vertex_array.hpp"
#include "gl/shader.hpp"
#include "io/input.hpp"
#include "io/input_event.hpp"
#include "systems/camera_system.hpp"
#include "systems/cube_system.hpp"
#include "systems/debug_system.hpp"
#include "renderer/cube_mesh.hpp"

namespace nith
{
    float Application::s_deltaTime = 1.0f / 60;

    entt::registry Registry; // global registry

    Application::Application():
        m_mainWindow("lmao gay", 1200, 850)
    {
        init_everything();

        m_mainWindow.open();
        m_mainWindow.setClearColor({ 0, 0, 0, 1 });
        m_mainWindow.toggleCursor(); // hide curosr by default
        m_mainWindow.center();

        // load resources
        ShaderLoader::Init();
        ShaderLoader::LoadAll();

        io::Input::SetCurrentWindow(&m_mainWindow);

        io::Input::GetEventDispatcher()
            .addEventListener<io::KeyPressedEvent>(
            [&](const io::KeyPressedEvent& event)
            {
                if (event.getKeyCode() == io::KeyCode::Escape)
                {
                    m_mainWindow.close();
                }
                else if (event.getKeyCode() == io::KeyCode::F1 && !event.isRepeat())
                {
                    m_mainWindow.toggleCursor();
                }
            }
        );

        // init imgui
        ImGui_ImplGlfw_InitForOpenGL(m_mainWindow.getNativeWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 430");

        // system init
        CameraSystem::Init();
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

        NITH_CLIENT_TRACE("Initialize [glfw] successfully");

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImFontConfig config;
        config.SizePixels = 16;
        config.OversampleH = 1;
        config.OversampleV = 1;
        config.PixelSnapH = true;
        io.Fonts->AddFontDefault(&config);

        NITH_CLIENT_TRACE("Initialize [imgui] successfully");

    }

    void Application::mainLoop()
    {
        m_mainWindow.makeCurrent();

        CubeSystem::CreateCube({ 0, 0, 0 }, { 0, 0, 0 }, { 1, 0, 0 });
        CubeSystem::CreateCube({ 0, 4, 0 }, { 1, 1, 1 }, { 1, 0, 0 });
        CubeSystem::CreateCube({ 2, 0, 0 }, { 1, 1, 1 }, { 1, 0, 0 });

        auto camera = CameraSystem::CreateCamera(m_mainWindow,
            1.0f * m_mainWindow.getWidth() / m_mainWindow.getHeight(), glm::radians(50.0f), 0.02, 2000);

        Registry.get<Transform>(camera).position.z += 5;
        Registry.get<Camera>(camera).updateViewMatrix(
            Registry.get<Transform>(camera)
        );

        glEnable(GL_DEPTH_TEST);

        auto lastTime = std::chrono::steady_clock::now();

        while (m_mainWindow.isOpen())
        {
            // input
            CameraSystem::Update(s_deltaTime);
            // render imgui
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            DebugSystem::Render(s_deltaTime);

            {
                ImGui::SetNextWindowBgAlpha(0.2);
                ImGui::SetNextWindowPos(ImVec2(10, 10));
                ImGui::SetNextWindowSize(ImVec2(150, 100));
                ImGui::Begin("Debug info");
                ImGui::Text("%.0f fps", 1 / s_deltaTime);
                ImGui::Text("%.0f ms/frame", s_deltaTime * 1000);
                ImGui::End();
            }

            ImGui::Render();

            // render
            m_mainWindow.beginLoop();

            CubeSystem::Render(camera, s_deltaTime);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            m_mainWindow.endLoop();

            // compute deltaTime
            auto currentTime = std::chrono::steady_clock::now();
            s_deltaTime = (currentTime - lastTime).count()/1000000000.0f;
            lastTime = currentTime;
        }
    }

    Application::~Application()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwTerminate();
    }
}
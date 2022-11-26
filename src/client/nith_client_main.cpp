#include "client/application.hpp"
#include "event.hpp"
#include "client/window_event.hpp"
#include "client/gl/shader.hpp"
#include "client/io/input.hpp"

int main()
{
    nith::Application gameApplication;
    
    /*nith::gl::Shader shader("basic_shader");

    shader.loadFromFile("D:/github/nith/assets/shaders/basic_material.vert",
        "D:/github/nith/assets/shaders/basic_material.frag");*/

    gameApplication.mainLoop();

    return EXIT_SUCCESS;
}
#include "client/application.hpp"
#include "event.hpp"
#include "client/window_event.hpp"
#include "client/gl/shader.hpp"
#include "client/io/input.hpp"
#include "client/gl/buffer.hpp"
#include "client/gl/vertex_array.hpp"

int main()
{
    nith::Application gameApplication;

    gameApplication.mainLoop();

    return EXIT_SUCCESS;
}
#include <iostream>

#include "softrender.hpp"

auto main(int, char*[]) -> int
{
    softrender::window_t window{ 1280, 720 };

    while(!window.closed()) {
        auto pos = window.get_mouse_position();
        std::cout << "Pos.x=" << pos.x << ", Pos.y=" << pos.y << std::endl;
        window.draw();
    }
}

#include "softrender.hpp"

auto main(int, char*[]) -> int
{
    using namespace softrender;
    window_t window{ 1280, 720 };

    while(!window.closed()) {
        window.draw();
    }
}

#include "softrender.hpp"

auto main(int, char*[]) -> int
{
    using namespace softrender;
    window_t window{ 1280, 720 };

    while(!window.closed()) {
        window.draw_rectangle(
            { window.width() / 2 - 300, window.height() / 2 - 300 },
            600,
            600,
            pink);
        window.draw_rectangle({ 20, 30 }, 200, 300, cyan);
        window.draw();
    }
}

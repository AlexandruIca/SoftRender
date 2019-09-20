#include "softrender.hpp"

auto main(int, char*[]) -> int
{
    softrender::window_t window{ 1280, 720 };

    while(!window.closed()) {
        window.draw_triangle(
            { window.width() / 2, window.height() / 2 - 200 },
            { window.width() / 2 - 200, window.height() / 2 + 200 },
            { window.width() / 2 + 200, window.height() / 2 + 200 },
            softrender::red);
        window.draw_triangle(
            { window.width() / 2, window.height() / 2 - 200 },
            { window.width() / 2 - 200, window.height() / 2 - 200 },
            { window.width() / 2 - 200, window.height() / 2 + 200 },
            softrender::amber);
        window.draw_triangle(
            { window.width() / 2, window.height() / 2 - 200 },
            { window.width() / 2 + 200, window.height() / 2 - 200 },
            { window.width() / 2 + 200, window.height() / 2 + 200 },
            softrender::indigo);
        window.draw_triangle(
            { 20, 20 }, { 160, 130 }, { 40, 380 }, softrender::blue);
        window.draw();
    }
}

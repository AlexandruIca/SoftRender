#include "softrender.hpp"

auto main(int, char*[]) -> int
{
    using namespace softrender;
    window_t window{ 1280, 720 };

    while(!window.closed()) {
        window.draw_line({ 30, 30 }, { 400, 400 }, { 255, 169, 47 });
        window.draw_line({ 30, 400 }, { 400, 30 }, { 168, 123, 123 });
        window.draw_line({ window.width() / 2 + 100, window.height() / 2 },
                         { window.width() / 2 - 100, window.height() / 2 },
                         pixel_t{ 255, 255, 255 });
        window.draw_line({ 700, 420 }, { 700, 120 }, { 128, 128, 128 });
        window.draw_line({ 700, 420 }, { 600, 120 }, { 200, 200, 200 });
        window.draw();
    }
}

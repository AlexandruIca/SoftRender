#include "softrender.hpp"

int main(int, char*[])
{
    using namespace softrender;
    window_t window{ 1280, 720 };

    while(!window.closed()) {
        // clang-format off
        for(int i = window.width() / 2 - 100;
                i <= window.width() / 2 + 100;
                ++i)
        // clang-format on
        {
            window.draw_point(window.height() / 2, i, pixel_t{ 255, 255, 255 });
        }
        window.draw();
    }
}


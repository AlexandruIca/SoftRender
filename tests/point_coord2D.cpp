#include "softrender.hpp"

#include <iostream>

int main(int, char*[])
{
    using namespace softrender;
    window_t window{ 1280, 720 };

    while(!window.closed()) {
        window.draw_point({ 0, 0 }, { 0, 255, 0 });
        window.draw_point({ 0, window.height() - 1 }, { 255, 255, 0 });
        window.draw_point({ window.width() - 1, 0 }, { 255, 255, 255 });
        window.draw_point({ window.width() - 1, window.height() - 1 },
                          { 255, 0, 0 });
        window.draw_point({ window.width() / 2, window.height() / 2 },
                          { 122, 122, 122 });
        window.draw();
    }
}

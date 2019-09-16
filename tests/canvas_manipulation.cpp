#include "softrender.hpp"

auto main(int, char*[]) -> int
{
    using namespace softrender;
    window_t window{ 1280, 720 };

    while(!window.closed()) {
        window.canvas()[window.from_coord2d_to_matrix(point_t{
            window.width() / 2, window.height() / 2 })] = pixel_t{ 255, 0, 0 };
        window.draw();
    }
}

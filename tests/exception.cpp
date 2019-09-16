#include <iostream>

#include "softrender.hpp"

auto main(int, char*[]) -> int
{
    try {
        using namespace softrender;
        window_t window;

        while(!window.closed()) {
            window.draw_point(1000, 1000, pixel_t{ 0, 0, 0, 0 });
            window.draw();
        }
    }
    catch(std::exception const& e) {
        std::cout << "Exception caught!" << std::endl << '\t';
        std::cout << e.what() << std::endl;
    }
}

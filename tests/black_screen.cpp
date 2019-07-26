#include "softrender.hpp"

int main()
{
    using namespace softrender;
    window_t window{ 1280, 720 };

    while(!window.closed()) {
        window.draw();
    }
}


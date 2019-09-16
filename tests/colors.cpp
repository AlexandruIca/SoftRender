#include <array>

#include "softrender.hpp"

auto main(int, char*[]) -> int
{
    using namespace softrender;

    std::array color = { colors::amber,  colors::black,  colors::blue,
                         colors::brown,  colors::cyan,   colors::green,
                         colors::grey,   colors::indigo, colors::lime,
                         colors::orange, colors::pink,   colors::purple,
                         colors::red,    colors::teal,   colors::white,
                         colors::yellow };

    window_t window{ 1280, 720 };

    while(!window.closed()) {
        for(int i = 0; i < color.size(); ++i) {
            window.draw_line({ window.width() / 2 - 100, (i + 1) * 20 },
                             { window.width() / 2 + 100, (i + 1) * 20 },
                             color[i]);
        }
        window.draw();
    }
}

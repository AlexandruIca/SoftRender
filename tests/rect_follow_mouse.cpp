#include <chrono>
#include <cmath>

#include "softrender.hpp"

struct rect_t
{
    softrender::point_t pos{ 0, 0 };
    int w{ 0 };
    int h{ 0 };
};

using microsecond_t =
    decltype(std::chrono::duration_cast<std::chrono::microseconds>(
                 std::chrono::seconds(1))
                 .count());

auto follow_mouse(rect_t& t_rect,
                  softrender::point_t const& t_mouse_pos,
                  microsecond_t const t_elapsed_time) noexcept -> void
{
    double const elapsed = t_elapsed_time / double{ 1e6 };

    int constexpr velocity = 300; // pixels

    double const center_x = t_rect.pos.x + t_rect.w / 2.0;
    double const center_y = t_rect.pos.y + t_rect.h / 2.0;

    double const dest_x = t_mouse_pos.x;
    double const dest_y = t_mouse_pos.y;

    double const dx = dest_x - center_x;
    double const dy = dest_y - center_y;

    double const distance = std::sqrt(dx * dx + dy * dy);

    if(distance < 5) {
        return;
    }

    t_rect.pos.x += velocity * elapsed * dx / distance;
    t_rect.pos.y += velocity * elapsed * dy / distance;
}

auto main(int, char*[]) -> int
{
    using namespace softrender;
    window_t window{ 1280, 720 };

    microsecond_t elapsed{ 0 };

    rect_t rect{ { window.width() / 2 - 200, window.height() / 2 - 200 },
                 400,
                 400 };

    auto start = std::chrono::high_resolution_clock::now();

    while(!window.closed()) {
        auto end = std::chrono::high_resolution_clock::now();
        elapsed =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start)
                .count();
        start = end;

        follow_mouse(rect, window.get_mouse_position(), elapsed);
        window.draw_rectangle(rect.pos, rect.w, rect.h, pink);
        window.draw();
    }
}

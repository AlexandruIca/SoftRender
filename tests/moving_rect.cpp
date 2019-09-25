#include <chrono>
#include <iostream>

#include "softrender.hpp"

struct rectangle_t
{
    softrender::point_t pos{ 0, 0 };
    int w{ 0 };
    int h{ 0 };
};

using microsecond_t =
    decltype(std::chrono::duration_cast<std::chrono::microseconds>(
                 std::chrono::seconds(1))
                 .count());

auto move_rect(rectangle_t& t_rect,
               softrender::key_event_t const& t_key_event,
               microsecond_t const t_elapsed_time) noexcept -> void
{
    using namespace softrender;

    double const elapsed_sec = t_elapsed_time / double{ 1e6 };
    int const move_factor = 300; // pixels

    if(t_key_event.keyc == key::vk_up) {
        t_rect.pos.y -= static_cast<int>(move_factor * elapsed_sec);
    }
    else if(t_key_event.keyc == key::vk_down) {
        t_rect.pos.y += static_cast<int>(move_factor * elapsed_sec);
    }
    else if(t_key_event.keyc == key::vk_left) {
        t_rect.pos.x -= static_cast<int>(move_factor * elapsed_sec);
    }
    else if(t_key_event.keyc == key::vk_right) {
        t_rect.pos.x += static_cast<int>(move_factor * elapsed_sec);
    }
}

auto main(int, char*[]) -> int
{
    using namespace softrender;
    window_t window{ 1280, 720 };

    rectangle_t rect{ { window.width() / 2 - 200, window.height() / 2 - 200 },
                      400,
                      400 };

    microsecond_t elapsed{ 0 };

    window.set_on_key_press_callback(
        [&elapsed, &rect](key_event_t const& t_ev) -> void {
            move_rect(rect, t_ev, elapsed);
        });

    auto start = std::chrono::high_resolution_clock::now();
    while(!window.closed()) {
        auto end = std::chrono::high_resolution_clock::now();
        elapsed =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start)
                .count();
        start = end;

        window.draw_rectangle(rect.pos, rect.w, rect.h, cyan);
        window.draw();
    }
}

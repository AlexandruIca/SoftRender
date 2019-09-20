#include <iostream>
#include <string>

#include "softrender.hpp"

auto main(int, char*[]) -> int
{
    softrender::window_t window{ 1280, 720 };

    window.set_on_mouse_callback(
        [](softrender::mouse_event_t const& t_event) noexcept -> void {
            std::string button_name =
                t_event.button == softrender::mouse_button::left
                    ? "left"
                    : t_event.button == softrender::mouse_button::right
                          ? "right"
                          : t_event.button == softrender::mouse_button::middle
                                ? "middle"
                                : "unkown";
            if(t_event.pressed) {
                std::cout << "Pressed " << button_name << std::endl;
            }
            else {
                std::cout << "Released " << button_name << std::endl;
            }
        });

    while(!window.closed()) {
        window.draw();
    }
}

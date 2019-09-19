#include <iostream>

#include "softrender.hpp"

auto main(int, char*[]) noexcept -> int
{
    softrender::window_t window{ 1280, 720 };

    window.set_on_key_press_callback(
        [](softrender::key_event_t const& t_key_event) noexcept->void {
            std::cout << "Key code: " << t_key_event.keyc << std::endl;
            std::cout << "Repeating: " << t_key_event.repeat << std::endl;
            std::cout << "Released: " << t_key_event.released << std::endl;

            if(t_key_event.keyc == softrender::key::vk_a) {
                std::cout << "Wowww! You pressed A" << std::endl;
            }
        });

    while(!window.closed()) {
        window.draw();
    }
}

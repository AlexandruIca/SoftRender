#include <array>
#include <random>

#include "softrender.hpp"
#include "wavefront_reader.hpp"

auto main(int, char*[]) -> int
{
    auto random_color = []() -> softrender::pixel_t {
        std::random_device rdev{};
        std::mt19937 rng{ rdev() };
        std::uniform_int_distribution<int> dist{ 0, 255 };

        return softrender::pixel_t{ dist(rng), dist(rng), dist(rng) };
    };

    softrender::window_t window{ 1280, 720 };
    softrender::wavefront_model_t model{ "african_head.obj" };

    while(!window.closed()) {
        for(int i = 0; i < model.nfaces(); ++i) {
            auto faces = model.face(i);
            std::array<softrender::vec2i, 3> screen_coords;

            for(auto const j : { 0, 1, 2 }) {
                auto world_coords = model.vert(faces[j]);
                screen_coords[j] =
                    softrender::vec2i{ static_cast<int>((1.f + world_coords.x) *
                                                        window.width() / 2),
                                       static_cast<int>((1.f - world_coords.y) *
                                                        window.height() / 2) };
            }

            window.draw_triangle(screen_coords[0],
                                 screen_coords[1],
                                 screen_coords[2],
                                 random_color());
        }
        window.draw();
    }
}

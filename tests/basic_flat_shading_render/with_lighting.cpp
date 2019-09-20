#include <array>
#include <random>

#include "softrender.hpp"
#include "wavefront_reader.hpp"

auto main(int, char*[]) -> int
{
    softrender::window_t window{ 800, 800 };
    softrender::wavefront_model_t model{ "african_head.obj" };

    while(!window.closed()) {
        for(int i = 0; i < model.nfaces(); ++i) {
            auto faces = model.face(i);
            std::array<softrender::vec2i, 3> screen_coords;
            std::array<softrender::vec3f, 3> world_coords;

            for(auto const j : { 0, 1, 2 }) {
                auto v = model.vert(faces[j]);

                world_coords[j] = v;
                screen_coords[j] = softrender::vec2i{
                    static_cast<int>((1.f + v.x) * window.width() / 2),
                    static_cast<int>((1.f - v.y) * window.height() / 2)
                };
            }

            auto normal = cross(world_coords[2] - world_coords[0],
                                world_coords[1] - world_coords[0])
                              .normalize();
            auto intensity = normal * softrender::vec3f{ 0.f, 0.f, -0.5f };

            if(intensity > 0) {
                window.draw_triangle(
                    screen_coords[0],
                    screen_coords[1],
                    screen_coords[2],
                    softrender::pixel_t{ static_cast<int>(162 * intensity),
                                         static_cast<int>(236 * intensity),
                                         static_cast<int>(65 * intensity) });
            }
        }
        window.draw();
    }
}

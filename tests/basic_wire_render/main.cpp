#include <iostream>

#include "softrender.hpp"
#include "wavefront_reader.hpp"

auto main(int, char*[]) -> int
{
    softrender::window_t window{ 800, 800 };
    softrender::wavefront_model_t model{ "african_head.obj" };

    while(!window.closed()) {
        for(int i = 0; i < model.nfaces(); ++i) {
            auto face = model.face(i);

            for(auto const j : { 0, 1, 2 }) {
                softrender::vec3f v0 = model.vert(face[j]);
                softrender::vec3f v1 = model.vert(face[(j + 1) % 3]);

                softrender::point_t start{
                    static_cast<int>((v0.x + 1.f) * window.width() / 2.f),
                    static_cast<int>((1.f - v0.y) * window.height() / 2.f)
                };
                softrender::point_t end{
                    static_cast<int>((v1.x + 1.f) * window.width() / 2.f),
                    static_cast<int>((1.f - v1.y) * window.height() / 2.f)
                };

                auto shrink_if_gt_800 = [](int& n) noexcept->void
                {
                    if(n >= 800) {
                        n = 799;
                    }
                };

                shrink_if_gt_800(start.x);
                shrink_if_gt_800(start.y);
                shrink_if_gt_800(end.x);
                shrink_if_gt_800(end.y);

                window.draw_line(start, end, softrender::white);
            }
        }

        window.draw();
    }
}

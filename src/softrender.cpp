///
/// \file
///
#include "softrender.hpp"
#include "SDL.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

namespace softrender {

auto error(std::string const&) -> void;

}

#ifndef SOFTRENDER_MOCKING

namespace graphics_impl {

auto sdl_error(std::string const& t_error) -> void
{
    std::cout << "Error: " << t_error << "\n\t";
    std::cout << "SDL: " << SDL_GetError() << std::endl << std::endl;
}

auto test() -> int
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        sdl_error("sdl could not be initialized");
        return EXIT_FAILURE;
    }

    std::cout << "It worked" << std::endl;

    SDL_Quit();

    return EXIT_SUCCESS;
}

auto initialize_sdl(SDL_Window*& t_window,
                    SDL_Renderer*& t_renderer,
                    int const t_width,
                    int const t_height) -> void
{
    using namespace softrender;

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        error("Could not initialize sdl!");
    }

    t_window = SDL_CreateWindow("SoftRender",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                t_width,
                                t_height,
                                SDL_WINDOW_SHOWN);

    if(t_window == nullptr) {
        error("Could not create window!");
    }

    SDL_SetWindowResizable(t_window, SDL_FALSE);

    t_renderer = SDL_CreateRenderer(t_window, -1, SDL_RENDERER_ACCELERATED);

    if(t_renderer == nullptr) {
        error("Could not create a renderer!");
    }
}

auto close_sdl(SDL_Window* t_window,
               SDL_Renderer* t_renderer,
               SDL_Texture* t_texture) -> void
{
    if(t_texture != nullptr) {
        SDL_DestroyTexture(t_texture);
    }
    SDL_DestroyRenderer(t_renderer);
    SDL_DestroyWindow(t_window);
    SDL_Quit();
}

namespace surface_info {

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
constexpr Uint32 rmask = 0xff000000;
constexpr Uint32 gmask = 0x00ff0000;
constexpr Uint32 bmask = 0x0000ff00;
constexpr Uint32 amask = 0x000000ff;
#else
constexpr Uint32 rmask = 0x000000ff;
constexpr Uint32 gmask = 0x0000ff00;
constexpr Uint32 bmask = 0x00ff0000;
constexpr Uint32 amask = 0xff000000;
#endif

} // namespace surface_info

auto draw(SDL_Renderer*& t_renderer,
          SDL_Texture*& t_texture,
          std::vector<softrender::pixel_t>& t_canvas,
          int const t_width,
          int const t_height,
          bool& t_running) -> void
{
    if(t_texture != nullptr) {
        SDL_DestroyTexture(t_texture);
    }

    using namespace surface_info;
    using namespace softrender;

    SDL_Surface* surface =
        SDL_CreateRGBSurfaceFrom(reinterpret_cast<void*>(t_canvas.data()),
                                 t_width,
                                 t_height,
                                 32,
                                 4 * t_width,
                                 rmask,
                                 gmask,
                                 bmask,
                                 amask);

    if(surface == nullptr) {
        error("Could not create surface to draw!");
    }

    t_texture = SDL_CreateTextureFromSurface(t_renderer, surface);

    SDL_Rect screen;
    screen.x = 0;
    screen.y = 0;
    screen.w = t_width;
    screen.h = t_height;

    SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
    SDL_RenderClear(t_renderer);
    SDL_RenderCopy(t_renderer, t_texture, nullptr, &screen);
    SDL_RenderPresent(t_renderer);
    SDL_FreeSurface(surface);

    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch(e.type) {
        case SDL_QUIT:
            t_running = false;
            break;
        case SDL_KEYDOWN:
            if(e.key.keysym.sym == SDLK_ESCAPE) {
                t_running = false;
            }
            break;
        default:
            break;
        }
    }
}

} // namespace graphics_impl

namespace impl = graphics_impl;

#else

namespace dummy_impl {

auto sdl_error(std::string const&) -> void
{
}

auto test() -> int
{
    return EXIT_SUCCESS;
}

auto initialize_sdl(SDL_Window*&, SDL_Renderer*&, int const, int const) -> void
{
}

auto close_sdl(SDL_Window*&, SDL_Renderer*&, SDL_Texture*&) -> void
{
}

auto draw(SDL_Renderer*,
          SDL_Texture*,
          std::vector<softrender::pixel_t>&,
          int,
          int,
          bool& t_running) -> void
{
    static int num_iterations{ 0 };
    t_running = (++num_iterations < 50);
}

} // namespace dummy_impl

namespace impl = dummy_impl;

#endif

///
/// \brief Wrapper around **SDL_GetError**.
///
static auto sdl_error(std::string const& t_error) -> void
{
    impl::sdl_error(t_error);
}

auto test() -> int
{
    return impl::test();
}

namespace {

[[nodiscard]] auto point_inside_triangle(softrender::vec3f const& t_point,
                                         softrender::vec3f const& t_v0,
                                         softrender::vec3f const& t_v1,
                                         softrender::vec3f const& t_v2) noexcept
    -> bool
{
    auto normal = softrender::cross(t_v1 - t_v0, t_v2 - t_v0);
    auto main_triangle_area = normal.norm();

    // Barycentric coordinates.
    // Find u, v, w (real numbers) so that u + v + w = 1, 0 <= u, v, w <= 1.
    // Let A = t_v0, B = t_v1, C = t_v2, P = t_point.
    // Then u is Area(CAP) / Area(ABC), v is Area(ABP) / Area(ABC), w=1-u-v
    // If any of u,v,w is > 1 or < 0 return false, otherwise true.
    // The area of a triangle is calculated using the cross product(normally it
    // is the length of the cross product <b>divided by 2</b> but we are not
    // dividing by 2 here because the area of the main triangle is also
    // divided by 2 and it simplifies.
    auto tmpvec = softrender::cross(t_v1 - t_v0, t_point - t_v0);
    auto u = tmpvec.norm() / main_triangle_area;

    if(normal * tmpvec < 0) {
        return false;
    }

    tmpvec = softrender::cross(t_v2 - t_v1, t_point - t_v1);
    auto v = tmpvec.norm() / main_triangle_area;

    if(normal * tmpvec < 0) {
        return false;
    }

    auto w = 1 - u - v;

    if(w < 0 || w > 1) {
        return false;
    }

    return true;
}

} // namespace

namespace softrender {

pixel_t::pixel_t(int t_red, int t_green, int t_blue, int t_alpha) noexcept
    : r{ std::byte(t_red) }
    , g{ std::byte(t_green) }
    , b{ std::byte(t_blue) }
    , a{ std::byte(t_alpha) }
{
}

auto error(std::string const& t_error) -> void
{
    sdl_error(t_error);
#ifdef SOFTRENDER_DEBUG
    throw std::runtime_error(t_error);
#endif
}

auto swap(point_t& t_point) -> void
{
    std::swap(t_point.x, t_point.y);
}

auto window_t::initialize_sdl() -> void
{
    impl::initialize_sdl(m_window, m_renderer, m_width, m_height);
}

auto window_t::construct_canvas() -> void
{
    m_canvas.resize(m_width * m_height);

    for(int i = 0; i < m_height; ++i) {
        for(int j = 0; j < m_width; ++j) {
            this->operator()(i, j) = pixel_t{};
        }
    }
}

window_t::window_t()
    : m_width{ 640 }
    , m_height{ 480 }
{
    this->initialize_sdl();
    this->construct_canvas();
}

window_t::window_t(int const t_width, int const t_height)
    : m_width{ t_width }
    , m_height{ t_height }
{
    this->initialize_sdl();
    this->construct_canvas();
}

window_t::~window_t() noexcept
{
    impl::close_sdl(m_window, m_renderer, m_texture);
}

auto window_t::width() const noexcept -> int
{
    return m_width;
}

auto window_t::height() const noexcept -> int
{
    return m_height;
}

auto window_t::draw() -> void
{
    impl::draw(m_renderer, m_texture, m_canvas, m_width, m_height, m_running);
}

auto window_t::draw_point(int const t_i, int const t_j, pixel_t const& t_pixel)
    -> void
{
    this->operator()(t_i, t_j) = t_pixel;
}

auto window_t::draw_point(point_t const& t_point, pixel_t const& t_pixel)
    -> void
{
    this->operator()(t_point.y, t_point.x) = t_pixel;
}

auto window_t::draw_line(point_t t_start, point_t t_end, pixel_t const& t_pixel)
    -> void
{
    bool steep{ false };

    if(std::abs(t_end.x - t_start.x) < std::abs(t_end.y - t_start.y)) {
        swap(t_start);
        swap(t_end);
        steep = true;
    }
    if(t_start.x > t_end.x) {
        std::swap(t_start, t_end);
    }

    int dx = t_end.x - t_start.x;
    int dy = t_end.y - t_start.y;
    int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = t_start.y;

    if(steep) {
        for(int x = t_start.x; x <= t_end.x; ++x) {
            this->draw_point({ y, x }, t_pixel);

            error2 += derror2;
            if(error2 > dx) {
                y += (t_end.y > t_start.y ? 1 : -1);
                error2 -= 2 * dx;
            }
        }
    }
    else {
        for(int x = t_start.x; x <= t_end.x; ++x) {
            this->draw_point({ x, y }, t_pixel);

            error2 += derror2;
            if(error2 > dx) {
                y += (t_end.y > t_start.y ? 1 : -1);
                error2 -= 2 * dx;
            }
        }
    }
}

auto window_t::draw_triangle(vec2i const& t_a,
                             vec2i const& t_b,
                             vec2i const& t_c,
                             pixel_t const& t_pixel) -> void
{
    vec2i bbox_min{ this->width() - 1, this->height() - 1 };
    vec2i bbox_max{ 0, 0 };

    bbox_min.x = std::max(0, std::min({ bbox_min.x, t_a.x, t_b.x, t_c.x }));
    bbox_min.y = std::max(0, std::min({ bbox_min.y, t_a.y, t_b.y, t_c.y }));
    bbox_max.x = std::min(this->width() - 1,
                          std::max({ bbox_max.x, t_a.x, t_b.x, t_c.x }));
    bbox_max.y = std::min(this->height() - 1,
                          std::max({ bbox_max.y, t_a.y, t_b.y, t_c.y }));

    vec2i point{ 0, 0 };

    for(point.x = bbox_min.x; point.x <= bbox_max.x; ++point.x) {
        for(point.y = bbox_min.y; point.y <= bbox_max.y; ++point.y) {
            if(!point_inside_triangle(vec3f(static_cast<float>(point.x),
                                            static_cast<float>(point.y),
                                            1.f),
                                      vec3f(static_cast<float>(t_a.x),
                                            static_cast<float>(t_a.y),
                                            1.f),
                                      vec3f(static_cast<float>(t_b.x),
                                            static_cast<float>(t_b.y),
                                            1.f),
                                      vec3f(static_cast<float>(t_c.x),
                                            static_cast<float>(t_c.y),
                                            1.f))) {
                continue;
            }
            this->draw_point(point_t{ point.x, point.y }, t_pixel);
        }
    }
}

auto window_t::closed() const noexcept -> bool
{
    return !m_running;
}

auto window_t::operator()(int const t_i, int const t_j) -> pixel_t&
{
#ifdef SOFTRENDER_DEBUG
    if(t_i * m_width + t_j >= m_width * m_height) {
        throw std::runtime_error("Canvas coordinates out of bounds.");
    }
#endif

    return m_canvas[t_i * m_width + t_j];
}

auto window_t::operator()(int const t_i, int const t_j) const -> pixel_t const&
{
#ifdef SOFTRENDER_DEBUG
    if(t_i * m_width + t_j >= m_width * m_height) {
        throw std::runtime_error("Canvas coordinates out of bounds.");
    }
#endif

    return m_canvas[t_i * m_width + t_j];
}

auto window_t::from_coord2d_to_matrix(point_t const& t_point) const noexcept
    -> int
{
    return t_point.y * m_width + t_point.x;
}

auto window_t::canvas() noexcept -> std::vector<pixel_t>&
{
    return m_canvas;
}

auto window_t::canvas() const noexcept -> std::vector<pixel_t> const&
{
    return m_canvas;
}

} // namespace softrender

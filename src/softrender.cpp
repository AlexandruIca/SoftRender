///
/// \file
///
#include "softrender.hpp"
#include "SDL.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

namespace softrender {

void error(std::string const&);

}

#ifndef SOFTRENDER_MOCKING

namespace graphics_impl {

void sdl_error(std::string const& t_error)
{
    std::cout << "Error: " << t_error << "\n\t";
    std::cout << "SDL: " << SDL_GetError() << std::endl << std::endl;
}

int test()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        sdl_error("sdl could not be initialized");
        return EXIT_FAILURE;
    }

    std::cout << "It worked" << std::endl;

    SDL_Quit();

    return EXIT_SUCCESS;
}

void initialize_sdl(SDL_Window*& t_window,
                    SDL_Renderer*& t_renderer,
                    int const t_width,
                    int const t_height)
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

void close_sdl(SDL_Window* t_window,
               SDL_Renderer* t_renderer,
               SDL_Texture* t_texture)
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

void draw(SDL_Renderer*& t_renderer,
          SDL_Texture*& t_texture,
          std::vector<softrender::pixel_t>& t_canvas,
          int const t_width,
          int const t_height,
          bool& t_running)
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

void sdl_error(std::string const&)
{
}

int test()
{
    return EXIT_SUCCESS;
}

void initialize_sdl(SDL_Window*&, SDL_Renderer*&, int const, int const)
{
}

void close_sdl(SDL_Window*&, SDL_Renderer*&, SDL_Texture*&)
{
}

void draw(SDL_Renderer*,
          SDL_Texture*,
          std::vector<softrender::pixel_t>&,
          int,
          int,
          bool& t_running)
{
    static int num_iterations{ 0 };
    t_running = (++num_iterations < 1000);
}

} // namespace dummy_impl

namespace impl = dummy_impl;

#endif

///
/// \brief Wrapper around **SDL_GetError**.
///
static void sdl_error(std::string const& t_error)
{
    impl::sdl_error(t_error);
}

int test()
{
    return impl::test();
}

namespace softrender {

pixel_t::pixel_t(int t_red, int t_green, int t_blue, int t_alpha) noexcept
    : r{ std::byte(t_red) }
    , g{ std::byte(t_green) }
    , b{ std::byte(t_blue) }
    , a{ std::byte(t_alpha) }
{
}

void error(std::string const& t_error)
{
    sdl_error(t_error);
#ifdef SOFTRENDER_DEBUG
    throw std::runtime_error(t_error);
#endif
}

void swap(point_t& t_point)
{
    std::swap(t_point.x, t_point.y);
}

void window_t::initialize_sdl()
{
    impl::initialize_sdl(m_window, m_renderer, m_width, m_height);
}

void window_t::construct_canvas()
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

int window_t::width() const noexcept
{
    return m_width;
}

int window_t::height() const noexcept
{
    return m_height;
}

void window_t::draw()
{
    impl::draw(m_renderer, m_texture, m_canvas, m_width, m_height, m_running);
}

void window_t::draw_point(int const t_i, int const t_j, pixel_t const& t_pixel)
{
    this->operator()(t_i, t_j) = t_pixel;
}

void window_t::draw_point(point_t const& t_point, pixel_t const& t_pixel)
{
    this->operator()(t_point.y, t_point.x) = t_pixel;
}

void window_t::draw_line(point_t t_start, point_t t_end, pixel_t t_pixel)
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

    for(int x = t_start.x; x <= t_end.x; ++x) {
        float t = (x - t_start.x) / static_cast<float>(t_end.x - t_start.x);
        int y = static_cast<int>((1.f - t) * t_start.y + t * t_end.y);

        if(steep) {
            this->draw_point({ y, x }, t_pixel);
        }
        else {
            this->draw_point({ x, y }, t_pixel);
        }
    }
}

bool window_t::closed() const noexcept
{
    return !m_running;
}

pixel_t& window_t::operator()(int const t_i, int const t_j)
{
#ifdef SOFTRENDER_DEBUG
    if(t_i * m_width + t_j >= m_width * m_height) {
        throw std::runtime_error("Canvas coordinates out of bounds.");
    }
#endif

    return m_canvas[t_i * m_width + t_j];
}

pixel_t const& window_t::operator()(int const t_i, int const t_j) const
{
#ifdef SOFTRENDER_DEBUG
    if(t_i * m_width + t_j >= m_width * m_height) {
        throw std::runtime_error("Canvas coordinates out of bounds.");
    }
#endif

    return m_canvas[t_i * m_width + t_j];
}

int window_t::from_coord2d_to_matrix(point_t const& t_point) const noexcept
{
    return t_point.y * m_width + t_point.x;
}

std::vector<pixel_t>& window_t::canvas() noexcept
{
    return m_canvas;
}

std::vector<pixel_t> const& window_t::canvas() const noexcept
{
    return m_canvas;
}

} // namespace softrender

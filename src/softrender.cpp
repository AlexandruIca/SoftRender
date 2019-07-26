///
/// \file
///
#include "softrender.hpp"
#include "SDL.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

///
/// \brief Wrapper around **SDL_GetError**.
///
static void sdl_error(std::string const& t_error)
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

namespace softrender {

pixel_t::pixel_t(int t_red, int t_green, int t_blue, int t_alpha) noexcept
    : r{std::byte(t_red)}
    , g{std::byte(t_green)}
    , b{std::byte(t_blue)}
    , a{std::byte(t_alpha)}
{}

void error(std::string const& t_error)
{
    sdl_error(t_error);
#ifdef SOFTRENDER_DEBUG
    throw std::runtime_error(t_error);
#endif
}

void window_t::initialize_sdl()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        error("Could not initialize sdl!");
    }

    m_window = SDL_CreateWindow("SoftRender", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, m_width, m_height,
                                SDL_WINDOW_SHOWN);

    if(m_window == nullptr) {
        error("Could not create window!");
    }

    SDL_SetWindowResizable(m_window, SDL_FALSE);

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    if(m_renderer == nullptr) {
        error("Could not create a renderer!");
    }
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
    : m_width{640}
    , m_height{480}
{
    this->initialize_sdl();
    this->construct_canvas();
}

window_t::window_t(int const t_width, int const t_height)
    : m_width{t_width}
    , m_height{t_height}
{
    this->initialize_sdl();
    this->construct_canvas();
}

window_t::~window_t() noexcept
{
    if(m_texture != nullptr) {
        SDL_DestroyTexture(m_texture);
    }
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

int window_t::width() const noexcept
{
    return m_width;
}

int window_t::height() const noexcept
{
    return m_height;
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

void window_t::draw()
{
    if(m_texture != nullptr) {
        SDL_DestroyTexture(m_texture);
    }

    using namespace surface_info;

    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
        reinterpret_cast<void*>(m_canvas.data()), m_width, m_height, 32,
        4 * m_width, rmask, gmask, bmask, amask);

    if(surface == nullptr) {
        error("Could not create surface to draw!");
    }

    m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);

    SDL_Rect screen;
    screen.x = 0;
    screen.y = 0;
    screen.w = m_width;
    screen.h = m_height;

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, nullptr, &screen);
    SDL_RenderPresent(m_renderer);
    SDL_FreeSurface(surface);

    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch(e.type) {
        case SDL_QUIT:
            m_running = false;
            break;
        case SDL_KEYDOWN:
            if(e.key.keysym.sym == SDLK_ESCAPE) {
                m_running = false;
            }
            break;
        default:
            break;
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

} // namespace softrender


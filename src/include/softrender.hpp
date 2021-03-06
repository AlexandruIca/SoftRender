#ifndef SOFTRENDER_HPP
#define SOFTRENDER_HPP
#pragma once

///
/// \file
///

#include <cstddef>
#include <functional>
#include <vector>

#include "keys.hpp"
#include "mouse_button.hpp"
#include "vec.hpp"

///
/// \defgroup unchecked_release No bound checking
///
/// \warning These are functions that will do no bound checking for you when you
///          are running in release mode. In debug mode they will throw a
///          runtime error.
///

///
/// \defgroup canvas_manipulation Canvas manipulation
///
/// These functions let you use the canvas directly but you shouldn't really
/// use them unless you absolutely have to.
///

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

///
/// \brief All key functionality is in this namespace.
///
namespace softrender {

///
/// \brief Struct to represent an rgba value.
///
struct pixel_t
{
    std::byte r = std::byte{ 0 };
    std::byte g = std::byte{ 0 };
    std::byte b = std::byte{ 0 };
    std::byte a = std::byte{ 255 };

    pixel_t() noexcept = default;
    ///
    /// Constructor for an easy to use interface for the user.
    /// Without this the usage would be something like:
    ///
    /// \code{.cpp}
    ///     pixel_t px;
    ///     px.r = std::byte{red_value};
    ///     px.g = std::byte{green_value};
    ///     px.b = std::byte{blue_value};
    ///     px.a = std::byte{alpha_value};
    /// \endcode
    ///
    /// With this the usage looks like this:
    ///
    /// \code{.cpp}
    ///     pixel_t px{ red_value, green_value, alpha_value };
    /// \endcode
    ///
    pixel_t(int t_red, int t_green, int t_blue, int t_alpha = 255) noexcept;
};

///
/// \brief Namespace that contains a few useful predefined colors so that you
///        don't always have to put some random numbers in \ref pixel_t
///        constructor.
///
inline namespace colors {

pixel_t const black{ 0, 0, 0 };       ///< Material black color.
pixel_t const white{ 255, 255, 255 }; ///< Material white color.
pixel_t const red{ 255, 0, 0 };       ///< Material red color.
pixel_t const green{ 0, 255, 0 };     ///< Material green color.
pixel_t const blue{ 0, 0, 255 };      ///< Material blue color.
pixel_t const cyan{ 0, 188, 212 };    ///< Material cyan color.
pixel_t const yellow{ 255, 235, 59 }; ///< Material yellow color.
pixel_t const lime{ 205, 220, 57 };   ///< Material lime color.
pixel_t const teal{ 0, 150, 136 };    ///< Material teal color.
pixel_t const purple{ 156, 39, 176 }; ///< Material purple color.
pixel_t const pink{ 236, 64, 122 };   ///< Material pink color.
pixel_t const indigo{ 63, 81, 181 };  ///< Material indigo color.
pixel_t const amber{ 255, 193, 7 };   ///< Material amber color.
pixel_t const orange{ 255, 152, 0 };  ///< Material orange color.
pixel_t const brown{ 121, 85, 72 };   ///< Material brown color.
pixel_t const grey{ 158, 158, 158 };  ///< Material grey color.

} // namespace colors

///
/// \brief Simple structure for representing a point in 2D space.
///
/// Examples:
/// * (x=0, y=0) is in the top left corner
/// * (x=0, y=$HEIGHT - 1) is in the bottom left corner
/// * (x=$WIDTH - 1, y=$HEIGHT - 1 is in the bottom right corner
///
struct point_t
{
    int x{ 0 };
    int y{ 0 };
};

///
/// \brief Swaps \p t_point.x and \p t_point.y.
///
/// \note Useful for draw_line and possibly for other future algorithms.
///
auto swap(point_t& t_point) -> void;

///
/// \brief Describes what a key event contains.
///
struct key_event_t
{
    int keyc{ key::vk_unknown }; ///< The actual [key](\ref key).
    bool repeat{ false };        ///< True if the key is being held.
    bool released{ false };      ///< True if the key is being released.
};

///
/// \brief Describes what a mouse event contains.
///
struct mouse_event_t
{
    point_t position{ 0, 0 }; ///< Position of the mouse relative to window.
    int button{
        0
    }; ///< The button which has been pressed/release, one of \ref mouse_button.
    bool pressed{
        true
    }; ///< True if the button is pressed, false if it's released.
};

///
/// \brief Use this to construct a window.
///
/// This is just a wrapper around SDL to construct a surface from memory and
/// blit it.
///
class window_t
{
private:
    std::vector<pixel_t> m_canvas;

    int m_width;
    int m_height;
    bool m_running{ true };

    SDL_Window* m_window{ nullptr };
    SDL_Renderer* m_renderer{ nullptr };
    SDL_Texture* m_texture{ nullptr };

    std::function<void(key_event_t const& t_key_event)> m_key_callback =
        [](key_event_t const&) noexcept -> void {};
    std::function<void(mouse_event_t const& t_mouse_event)> m_mouse_callback =
        [](mouse_event_t const&) noexcept -> void {};

    auto construct_canvas() -> void;
    auto initialize_sdl() -> void;

public:
    ///
    /// \brief Constructs a window with width=640, height=480.
    ///
    window_t();
    ///
    /// \brief Constructs a window with \p t_width width and \p t_height
    ///        height.
    ///
    window_t(int const t_width, int const t_height);
    ~window_t() noexcept;

    ///
    /// \brief Get width of constructed window.
    ///
    [[nodiscard]] auto width() const noexcept -> int;
    ///
    /// \brief Get height of constructed window.
    ///
    [[nodiscard]] auto height() const noexcept -> int;

    ///
    /// \brief Draws everything to the screen and handles input.
    ///
    /// \note If you press \ref key::vk_escape the application exits.
    ///
    auto draw() -> void;

    ///
    /// \brief Draws a point at coordinate (x=\p t_j, y=\p t_i).
    ///
    /// \ingroup unchecked_release
    ///
    /// \param[in] t_i The line on which the pixel will be put.
    /// \param[in] t_j The column on which the pixel will be put.
    /// \param[in] t_pixel The color of the point.
    ///
    auto draw_point(int const t_i, int const t_j, pixel_t const& t_pixel)
        -> void;

    ///
    /// \brief Draws a point using a more traditional approach(x and y
    ///        coordinates instead of lines and columns in a matrix).
    ///
    /// \ingroup unchecked_release
    ///
    auto draw_point(point_t const& t_point, pixel_t const& t_pixel = pixel_t{})
        -> void;

    ///
    /// \brief Draws a line from \p t_start to \p t_end with color \p t_pixel.
    ///
    auto draw_line(point_t t_start,
                   point_t t_end,
                   pixel_t const& t_pixel = pixel_t{}) -> void;

    ///
    /// \brief Draws a triangle with given coordinates.
    ///
    auto draw_triangle(vec2i const& t_a,
                       vec2i const& t_b,
                       vec2i const& t_c,
                       pixel_t const& t_pixel = pixel_t{}) -> void;

    ///
    /// \brief Draws a rectangle starting at (\p t_pos.x, \p t_pos.y) with
    ///        width=\p t_width and height=\p t_height.
    ///
    auto draw_rectangle(point_t const& t_pos,
                        int const t_width,
                        int const t_height,
                        pixel_t const& t_pixel = pixel_t{}) -> void;

    ///
    /// \brief Returns true if the window will close.
    ///
    /// \ingroup unchecked_release
    ///
    /// \note If you press ESCAPE the application terminates.
    ///
    [[nodiscard]] auto closed() const noexcept -> bool;

    ///
    /// \brief Access the rgba value at line=\p t_i and column=\p t_j.
    ///
    /// \ingroup unchecked_release
    ///
    /// \param t_i Line of the inner rgba matrix.
    /// \param t_j Column of the inner rgba matrix.
    ///
    [[nodiscard]] auto operator()(int const t_i, int const t_j) -> pixel_t&;
    ///
    /// \brief Get a const reference to the rgba value at line=\p t_i and
    ///        column=\p t_j.
    ///
    /// \ingroup unchecked_release
    ///
    /// \param t_i Line of the inner rgba matrix.
    /// \param t_j Column of the inner rgba matrix.
    ///
    [[nodiscard]] auto operator()(int const t_i, int const t_j) const
        -> pixel_t const&;

    ///
    /// \brief Returns corresponding position in the rgba matrix of a point
    ///        \p t_point as if the canvas was a 2d matrix.
    ///
    /// With this you could say:
    ///
    /// \code{.cpp}
    ///     this->canvas()[this->from_coord2d_to_matrix({
    ///         x=20, y=30
    ///     })];
    /// \endcode
    ///
    /// which is equivalent to this:
    ///
    /// \code{.cpp}
    ///     this->operator()(x=20, y=30);
    /// \endcode
    ///
    /// This will (hopefully) be useful for further optimizations for different
    /// algorithms(for example: draw_rect).
    ///
    /// \ingroup canvas_manipulation
    ///
    [[nodiscard]] auto from_coord2d_to_matrix(point_t const& t_point) const
        noexcept -> int;

    ///
    /// \brief Returns the underlying canvas/matrix with rgba values.
    ///
    /// \ingroup canvas_manipulation
    ///
    [[nodiscard]] auto canvas() noexcept -> std::vector<pixel_t>&;
    ///
    /// \brief Returns the underlying canvas/matrix with rgba values.
    ///
    /// \ingroup canvas_manipulation
    ///
    [[nodiscard]] auto canvas() const noexcept -> std::vector<pixel_t> const&;

    ///
    /// \brief Provide a function that will be called on each key press.
    ///
    /// \param t_function Must be a function accepting a const \ref key_event_t
    ///                   &.
    ///
    template<typename F>
    auto set_on_key_press_callback(F t_function) -> void
    {
        m_key_callback = t_function;
    }

    ///
    /// \brief Provide a function that will be called on each mouse button
    ///        press/release.
    ///
    /// \param t_function Must be a function accepting a const \ref
    ///                   mouse_event_t &.
    ///
    template<typename F>
    auto set_on_mouse_callback(F t_function) -> void
    {
        m_mouse_callback = t_function;
    }

    ///
    /// \returns A \ref point_t with the current mouse position relative to the
    ///          window.
    ///
    [[nodiscard]] auto get_mouse_position() const noexcept -> point_t;
};

} // namespace softrender

auto test() -> int;

#endif // !SOFTRENDER_HPP

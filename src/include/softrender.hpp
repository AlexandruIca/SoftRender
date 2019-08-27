///
/// \file
///

#include <cstddef>
#include <vector>

///
/// \defgroup unchecked_release No bound checking
///
/// \warning These are functions that will do no bound checking for you when you
///          are running in release mode.
///

///
/// \defgroup canvas_manipulation Canvas manipulation
///
/// These functions let you use the canvas directly but you shouldn't really use
/// them unless you absolutely have to.
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
/// \brief Use this to construct a window.
///
/// This is just a wrapper around SDL to construct a surface from memory and
/// blit it.
///
/// \note There is no separate renderer class to keep the code super simple.
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

    void construct_canvas();
    void initialize_sdl();

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
    int width() const noexcept;
    ///
    /// \brief Get height of constructed window.
    ///
    int height() const noexcept;

    ///
    /// \brief Draws everything to the screen and handles input.
    ///
    /// \note There are no separate functions (yet) to retreive events
    ///       to keep the code simple, but when the need arises they will
    ///       be added to the class. Currently, if you press ESCAPE the
    ///       application exits.
    ///
    void draw();

    ///
    /// \brief Draws a point at coordinate (x=\p t_j, y=\p t_i).
    ///
    /// \ingroup unchecked_release
    ///
    /// \param t_i The line on which the pixel will be put.
    /// \param t_j The column on which the pixel will be put.
    /// \param t_pixel The color of the point.
    ///
    void draw_point(int const t_i, int const t_j, pixel_t const& t_pixel);

    ///
    /// \brief Draws a point using a more traditional approach(x and y
    ///        coordinates instead of lines and columns in a matrix).
    ///
    /// \ingroup unchecked_release
    ///
    void draw_point(point_t const& t_point, pixel_t const& t_pixel);

    ///
    /// \brief Returns true if the window will close.
    ///
    /// \ingroup unchecked_release
    ///
    /// \note If you press ESCAPE the application terminates.
    ///
    bool closed() const noexcept;

    ///
    /// \brief Access the rgba value at line=\p t_i and column=\p t_j.
    ///
    /// \ingroup unchecked_release
    ///
    /// \param t_i Line of the inner rgba matrix.
    /// \param t_j Column of the inner rgba matrix.
    ///
    pixel_t& operator()(int const t_i, int const t_j);
    ///
    /// \brief Get a const reference to the rgba value at line=\p t_i and
    ///        column=\p t_j.
    ///
    /// \ingroup unchecked_release
    ///
    /// \param t_i Line of the inner rgba matrix.
    /// \param t_j Column of the inner rgba matrix.
    ///
    pixel_t const& operator()(int const t_i, int const t_j) const;

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
    int from_coord2d_to_matrix(point_t const& t_point) const noexcept;

    ///
    /// \brief Returns the underlying canvas/matrix with rgba values.
    ///
    /// \ingroup canvas_manipulation
    ///
    std::vector<pixel_t>& canvas() noexcept;
    ///
    /// \brief Returns the underlying canvas/matrix with rgba values.
    ///
    /// \ingroup canvas_manipulation
    ///
    std::vector<pixel_t> const& canvas() const noexcept;
};

} // namespace softrender

int test();

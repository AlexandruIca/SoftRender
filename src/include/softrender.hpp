///
/// \file
///

#include <cstddef>
#include <vector>

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
    std::byte r = std::byte{0};
    std::byte g = std::byte{0};
    std::byte b = std::byte{0};
    std::byte a = std::byte{255};

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
    pixel_t(int t_red, int t_green, int t_blue, int t_alpha) noexcept;
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
    bool m_running{true};

    SDL_Window* m_window{nullptr};
    SDL_Renderer* m_renderer{nullptr};
    SDL_Texture* m_texture{nullptr};

    void construct_canvas();
    void initialize_sdl();

public:
    ///
    /// \brief Constructs a window with width=640, height=480.
    ///
    window_t();
    ///
    /// \brief Constructs a window with \ref t_width width and t_height
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
    /// \brief Returns true if the window will close.
    ///
    /// \note If you press ESCAPE the application terminates.
    ///
    bool closed() const noexcept;

    ///
    /// \brief Access the rgba value at [line](\ref t_i) and [column](\ref t_j).
    ///
    /// \param t_i Line of the inner rgba matrix.
    /// \param t_j Column of the inner rgba matrix.
    ///
    pixel_t& operator()(int const t_i, int const t_j);
    ///
    /// \brief Get a const reference to the rgba value at [line](\ref t_i) and
    ///        [column](\ref t_j).
    ///
    /// \param t_i Line of the inner rgba matrix.
    /// \param t_j Column of the inner rgba matrix.
    ///
    pixel_t const& operator()(int const t_i, int const t_j) const;
};

} // namespace softrender

int test();


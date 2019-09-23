#include <algorithm>
#include <array>
#include <random>
#include <vector>

#include "softrender.hpp"

namespace {

constexpr int g_window_width = 800;
constexpr int g_window_height = 800;

} // namespace

namespace game_grid {

constexpr int width = 10;
constexpr int height = 10;

} // namespace game_grid

struct rectangle_t
{
    softrender::point_t pos{ 0, 0 };
    int w{ 0 };
    int h{ 0 };
};

enum class grid_cell_state
{
    empty = 0,
    fruit,
    snake
};

struct game_state_t
{
    softrender::point_t fruit_position{ 0, 0 };
    std::vector<softrender::point_t> snake_position;
    std::array<std::array<grid_cell_state, game_grid::height>, game_grid::width>
        grid;
};

auto generate_random_position(game_state_t& t_state) noexcept
    -> softrender::point_t
{
    static std::random_device rdev{};
    static std::mt19937 rng{ rdev() };
    static std::uniform_int_distribution<int> width_dist{ 0, game_grid::width };
    static std::uniform_int_distribution<int> height_dist{ 0,
                                                           game_grid::height };

    int x = width_dist(rng);
    int y = height_dist(rng);

    while(t_state.grid[x][y] != grid_cell_state::empty) {
        x = width_dist(rng);
        y = height_dist(rng);
    }

    return softrender::point_t{ x, y };
}

auto init_game(game_state_t& t_state) noexcept -> void
{
    for(auto& line : t_state.grid) {
        line.fill(grid_cell_state::empty);
    }
    t_state.snake_position.push_back(
        { game_grid::width / 2, game_grid::height / 2 });
    t_state.snake_position.push_back(
        { game_grid::width / 2, game_grid::height / 2 + 1 });
    t_state.snake_position.push_back(
        { game_grid::width / 2, game_grid::height / 2 + 2 });

    for(auto const& pos : t_state.snake_position) {
        t_state.grid[pos.x][pos.y] = grid_cell_state::snake;
    }

    t_state.fruit_position = generate_random_position(t_state);
    t_state.grid[t_state.fruit_position.x][t_state.fruit_position.y] =
        grid_cell_state::fruit;
}

auto grid_to_screen_coords(int const t_x, int const t_y) noexcept -> rectangle_t
{
    constexpr int cell_width = g_window_width / game_grid::width;
    constexpr int cell_height = g_window_height / game_grid::height;

    return { softrender::point_t{ t_x * cell_width, t_y * cell_height },
             cell_width,
             cell_height };
}

auto draw_game_state(softrender::window_t& t_window,
                     game_state_t& t_state) noexcept -> void
{
    int x{ 0 };

    for(auto const& line : t_state.grid) {
        int y{ 0 };

        for(auto const cell : line) {
            switch(cell) {
            case grid_cell_state::fruit: {
                auto rect = grid_to_screen_coords(x, y);

                t_window.draw_rectangle(
                    rect.pos, rect.w, rect.h, softrender::yellow);

                break;
            }
            case grid_cell_state::snake: {
                auto color = softrender::purple;
                // snakex, snakey
                auto const [sx, sy] = t_state.snake_position.front();

                if(sx == x && sy == y) {
                    // draw head, different color
                    color = softrender::blue;
                }

                auto const rect = grid_to_screen_coords(x, y);
                t_window.draw_rectangle(rect.pos, rect.w, rect.h, color);

                break;
            }
            default: {
                break;
            }
            }

            ++y;
        }

        ++x;
    }
}

auto main(int, char*[]) -> int
{
    using namespace softrender;
    window_t window{ g_window_width, g_window_height };

    game_state_t state;

    init_game(state);

    while(!window.closed()) {
        draw_game_state(window, state);
        window.draw();
    }

    return 0;
}

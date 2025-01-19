#pragma once

#include "constants.hpp"

#include "texture_manager.hpp"
#include <filesystem>
#include <vector>

namespace botman
{

enum class Tile
{
    EMPTY,
    WALL,
    PELLET,
    START_POS,
    SPAWNER,
    HAMMER,
};

class Map
{
public:
    Map(const vec2& pos, const std::filesystem::path& path, TextureManager& tm);
    Map(const vec2& pos, TextureManager& tm) : m_tm{tm}, m_pos{pos} {}

    auto draw() const -> void;

    auto load_from_file(const std::filesystem::path& path) -> void;
    auto save_to_file(const std::filesystem::path& path) -> void;

    // grid - local to map grid position,
    // pos - global space on the screen
    auto get_pos_from_grid(const vec2& grid_pos) const -> vec2;
    // grid - local to map grid position,
    // pos - global space on the screen
    auto get_grid_from_pos(const vec2& pos) const -> vec2;

    auto in_about_center(const vec2& pos) const -> bool;

    inline auto get_start_pos() const -> const vec2& { return m_start_pos; }
    inline auto get_tiles() const -> const std::array<std::array<Tile, constants::MAP_HEIGHT>, constants::MAP_WIDTH>& { return m_tiles; }

private:
    auto m_draw_grid() const -> void;
    auto m_draw_walls() const -> void;
    auto m_draw_pellets() const -> void;
    auto m_draw_hammers() const -> void;
    auto m_draw_spawner() const -> void;

private:
    TextureManager& m_tm;

    vec2 m_pos;

    std::array<std::array<Tile, constants::MAP_HEIGHT>, constants::MAP_WIDTH> m_tiles{};
    std::vector<vec2> m_walls{};
    std::vector<vec2> m_pellets{};
    std::vector<vec2> m_hammers{};
    vec2 m_start_pos{};
    vec2 m_spawner_pos{};

};

}

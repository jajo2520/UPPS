#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace physics
{
    inline glm::vec2 GRAVITY {0.0f, -250.0f};
    inline constexpr float COFR {.05};
}

namespace simulation 
{
    inline constexpr float TIME_STEP {1.0/600};
    inline int COLLISIONS {};
    inline int TOTAL_COLLISIONS {};
    inline int FRAME_COUNT {};
}

namespace screen
{
    inline constexpr float SCREEN_WIDTH {1600.f};
    inline constexpr float SCREEN_HEIGHT {800.f};
    inline constexpr float CELL_SIZE {1.f};
    inline constexpr int ROW_NUM {static_cast<int>(SCREEN_HEIGHT / CELL_SIZE)};
    inline constexpr int COL_NUM {static_cast<int>(SCREEN_WIDTH / CELL_SIZE)};
}

namespace geometry
{
    inline constexpr float WALL_LEFT {50.0f};
    inline constexpr float WALL_RIGHT {screen::SCREEN_WIDTH - 50.f};
    inline constexpr float FLOOR {50.0f};
    inline constexpr float CEILING {screen::SCREEN_HEIGHT - 50.f};
    inline constexpr float P_RADIUS {0.9f};
    inline constexpr int P_NUMBER {5200};
    inline constexpr int VERT_NUMBER {5};
    inline std::vector<float> P_VERTICES (2*(VERT_NUMBER+2));
}


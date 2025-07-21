#pragma once
#include "glm/glm.hpp"

namespace physics
{
    inline constexpr glm::vec2 GRAVITY {0.0f, -400.0f};
    inline constexpr float COFR {0.8};
}

namespace simulation 
{
    inline constexpr float TIME_STEP {0.0167};
}

namespace geometry
{
    inline constexpr float WALL_LEFT {50.0f};
    inline constexpr float WALL_RIGHT {750.0f};
    inline constexpr float FLOOR {50.0f};
    inline constexpr float P_RADIUS {5.0f};
}

namespace screen
{
    inline constexpr float SCREEN_WIDTH {800.f};
    inline constexpr float SCREEN_HEIGHT {800.f};
}

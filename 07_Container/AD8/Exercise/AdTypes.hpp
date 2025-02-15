#pragma once

#include <cstdint>
#include <array>

#include "AdConstants.hpp"

enum class LaneAssociationType
{
    LEFT,
    CENTER,
    RIGHT,
    NONE,
};

struct VehicleType
{
    std::int32_t id;
    LaneAssociationType lane;
    float speed_mps;
    float distance_m;
};

struct NeighborVehiclesType
{
    std::array<VehicleType, NUM_VEHICLES_ON_LANE> vehicles_left_lane;
    std::array<VehicleType, NUM_VEHICLES_ON_LANE> vehicles_center_lane;
    std::array<VehicleType, NUM_VEHICLES_ON_LANE> vehicles_right_lane;
};

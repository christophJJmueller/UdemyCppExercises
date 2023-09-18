#pragma once

#include <cstdint>

#include "AdConstants.hpp"

enum class LaneAssociationType
{
    LEFT,
    CENTER,
    RIGHT,
    UNKNOWN,
};

struct VehicleType
{
    std::int32_t id;// Id
    LaneAssociationType lane;// Lane
    float speed_mps;// Speed (meter/s)
    float rel_distance_m;// Relative Distance (meter)
};

struct NeighborVehiclesType
{
    VehicleType left_lane_vehicles[NUM_VEHICLES_ON_LANE];// Array for nearby vehicles on left lane (2 vehicles in total)
    VehicleType center_lane_vehicles[NUM_VEHICLES_ON_LANE];// Array for nearby vehicles on center lane (2 vehicles in total)
    VehicleType right_lane_vehicles[NUM_VEHICLES_ON_LANE];// Array for nearby vehicles on right lane (2 vehicles in total)
};

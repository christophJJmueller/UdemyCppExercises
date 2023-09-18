#include <cmath>
#include <cstdint>
#include <iostream>

#include "AdConstants.hpp"
#include "AdFunctions.hpp"

float kph_to_mps(const float kph)
{
    return kph /3.6F;
}

void init_ego_vehicle(VehicleType &ego_vehicle)
{
    ego_vehicle.id = EGO_VEHICLE_ID;
    ego_vehicle.lane = LaneAssociationType::CENTER;
    ego_vehicle.speed_mps = kph_to_mps(135.0F);
    ego_vehicle.rel_distance_m = 0.0F;

}

void init_vehicle(VehicleType &vehicle,
                  const std::int32_t id,
                  const float speed_kph,
                  const float distance_m,
                  const LaneAssociationType lane)
{
    vehicle.id = id;
    vehicle.speed_mps = kph_to_mps(speed_kph);
    vehicle.rel_distance_m = distance_m;
    vehicle.lane = lane;

}

void init_vehicles(NeighborVehiclesType &vehicles)
{
    init_vehicle(vehicles.left_lane_vehicles[0],0,100.0F,20.0F,LaneAssociationType::LEFT);
    init_vehicle(vehicles.left_lane_vehicles[1],1,130.0F,-50.0F,LaneAssociationType::LEFT);
    init_vehicle(vehicles.center_lane_vehicles[0],0,80.0F,-10.0F,LaneAssociationType::CENTER);
    init_vehicle(vehicles.center_lane_vehicles[1],1,100.0F,100.0F,LaneAssociationType::CENTER);
    init_vehicle(vehicles.right_lane_vehicles[0],0,90.0F,0.0F,LaneAssociationType::RIGHT);
    init_vehicle(vehicles.right_lane_vehicles[1],1,120.0F,10.0F,LaneAssociationType::RIGHT);
}

void print_vehicle(const VehicleType &vehicle)
{
    std::cout << "Vehicle ID: " << vehicle.id << ", speed [m/s]: " << vehicle.speed_mps << ", distance [m]: " << vehicle.rel_distance_m;

    switch (vehicle.lane)
    {
    case LaneAssociationType::LEFT:
        std::cout << ", Lane Association: Left" << std::endl;
        break;
    case LaneAssociationType::CENTER:
        std::cout << ", Lane Association: Center" << std::endl;
        break;
    case LaneAssociationType::RIGHT:
        std::cout << ", Lane Association: Right" << std::endl;
        break;
    case LaneAssociationType::UNKNOWN:
    default:
        std::cout << ", Lane Association: Unknown" << std::endl;
        break;
    }
}

void print_neighbor_vehicles(const NeighborVehiclesType &vehicles)
{
    print_vehicle(vehicles.left_lane_vehicles[0]);
    print_vehicle(vehicles.left_lane_vehicles[1]);
    print_vehicle(vehicles.center_lane_vehicles[0]);
    print_vehicle(vehicles.center_lane_vehicles[1]);
    print_vehicle(vehicles.right_lane_vehicles[0]);
    print_vehicle(vehicles.right_lane_vehicles[1]);
}

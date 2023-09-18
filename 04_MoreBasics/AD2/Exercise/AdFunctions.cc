#include <cmath>
#include <cstdint>
#include <iostream>

#include "AdConstants.hpp"
#include "AdFunctions.hpp"

float kph_to_mps(const float kph)
{
    return kph / 3.6F;
}

void init_ego_vehicle(VehicleType &ego_vehicle)
{
    ego_vehicle.id = EGO_VEHICLE_ID;
    ego_vehicle.speed_mps = kph_to_mps(135.0F);
    ego_vehicle.distance_m = 0.0F;
    ego_vehicle.lane = LaneAssociationType::CENTER;
}

void init_vehicle(VehicleType &vehicle,
                  const std::int32_t id,
                  const float speed_kph,
                  const float distance_m,
                  const LaneAssociationType lane)
{
    vehicle.id = id;
    vehicle.speed_mps = kph_to_mps(speed_kph);
    vehicle.distance_m = distance_m;
    vehicle.lane = lane;
}

void init_vehicles(NeighborVehiclesType &vehicles)
{
    init_vehicle(vehicles.vehicles_left_lane[0],
                 0,
                 130.0F,
                 80.0F,
                 LaneAssociationType::LEFT);
    init_vehicle(vehicles.vehicles_left_lane[1],
                 1,
                 80.0F,
                 -20.0F,
                 LaneAssociationType::LEFT);
    init_vehicle(vehicles.vehicles_center_lane[0],
                 2,
                 80.0F,
                 50.0F,
                 LaneAssociationType::CENTER);
    init_vehicle(vehicles.vehicles_center_lane[1],
                 3,
                 120.0F,
                 -50.0F,
                 LaneAssociationType::CENTER);
    init_vehicle(vehicles.vehicles_right_lane[0],
                 4,
                 110.0F,
                 30.0F,
                 LaneAssociationType::RIGHT);
    init_vehicle(vehicles.vehicles_right_lane[1],
                 5,
                 90.0F,
                 -30.0F,
                 LaneAssociationType::RIGHT);
}

void print_vehicle(const VehicleType &vehicle)
{
    std::cout << "ID: " << vehicle.id << '\n';
    std::cout << "Speed (m/s): " << vehicle.speed_mps << '\n';
    std::cout << "Distance (m): " << vehicle.distance_m << '\n';
    std::cout << "Lane: " << static_cast<std::int32_t>(vehicle.lane) << '\n';
}

void print_neighbor_vehicles(const NeighborVehiclesType &vehicles)
{
    print_vehicle(vehicles.vehicles_left_lane[0]);
    print_vehicle(vehicles.vehicles_left_lane[1]);
    print_vehicle(vehicles.vehicles_center_lane[0]);
    print_vehicle(vehicles.vehicles_center_lane[1]);
    print_vehicle(vehicles.vehicles_right_lane[0]);
    print_vehicle(vehicles.vehicles_right_lane[1]);
}

void print_vehicle_on_lane(const VehicleType *const vehicle,
                           const float range_m,
                           const float offset_m,
                           char *string,
                           std::size_t &idx)
{
    if ((&vehicle != nullptr) && (range_m >= vehicle->distance_m) && (vehicle->distance_m > (range_m - offset_m)))
    {
        string[1] = 'V';
        idx++;
    }
    else if ((&vehicle != nullptr) && (std::abs(vehicle->distance_m > VIEW_RANGE_M)))
    {
        idx++;
    }


}

void print_scene(const VehicleType &ego_vehicle,
                 const NeighborVehiclesType &vehicles)
{

    //Hilfsvariablen für Fahrzeuge
    std::size_t left_idx = 0;
    std::size_t center_idx = 0;
    std::size_t right_idx = 0;


    auto row_resolution = 0;
    std::cout << "Please enter the desired row resolution in meters: " << std::endl;
    std::cin >> row_resolution;

    std::cout << "    \t   L     C     R  \n";

    //Umwandlung VIEW_RANGE_M von float nach int, um in for-Schleife nutzen zu können
    auto view_range_m = static_cast<std::int32_t>(VIEW_RANGE_M);

    for (auto i = view_range_m; i >= -view_range_m; i -=row_resolution)
    {
        //Umwandlung i in float, um mit vehicle.distance vergleichen zu können
        //range 100 == [100...80)
        //range 80 == [80 ... 60)
        auto current_range = static_cast<float>(i);

        //Default-String-Arrays als Vorlage für Consolenausgabe -> mittleres Symbol wird im Bedarfsfall beschrieben
        char left_string[]{"   "};
        char center_string[]{"   "};
        char rigth_string[]{"   "};

        //Abfrage Ego-Vehicle
        if ((current_range >= ego_vehicle.distance_m) && (ego_vehicle.distance_m > (current_range - row_resolution)))
        {
            center_string[1] = 'E';
        }

        //Abfrage weitere Fahrzeuge
        //Hinweis: Zur Vereinfachung ist aktuell das Fahrzeug mit Index 0 "vor" Index 1

        if (left_idx < NUM_VEHICLES_ON_LANE)
        {
            print_vehicle_on_lane(&vehicles.vehicles_left_lane[left_idx], current_range, row_resolution, left_string, left_idx);
        }

        if (center_idx < NUM_VEHICLES_ON_LANE)
        {
            print_vehicle_on_lane(&vehicles.vehicles_center_lane[center_idx], current_range, row_resolution, center_string, center_idx);
        }

        if (right_idx < NUM_VEHICLES_ON_LANE)
        {
            print_vehicle_on_lane(&vehicles.vehicles_right_lane[right_idx], current_range, row_resolution, rigth_string, right_idx);
        }

        //finale Consolenausgabe
        std::cout << i << '\t' << left_string << " | " << center_string << " | " << rigth_string << " | \n";
    }

}

void compute_future_distance(VehicleType &vehicle,
                             const float ego_driven_distance,
                             const float seconds)
{
    const auto driven_distance = vehicle.speed_mps * seconds;
    vehicle.distance_m += (driven_distance - ego_driven_distance);
}

void compute_future_state(const VehicleType &ego_vehicle,
                          NeighborVehiclesType &vehicles,
                          const float seconds)
{
    const auto ego_driven_distance = ego_vehicle.speed_mps * seconds;

    compute_future_distance(vehicles.vehicles_left_lane[0],
                            ego_driven_distance,
                            seconds);
    compute_future_distance(vehicles.vehicles_left_lane[1],
                            ego_driven_distance,
                            seconds);
    compute_future_distance(vehicles.vehicles_center_lane[0],
                            ego_driven_distance,
                            seconds);
    compute_future_distance(vehicles.vehicles_center_lane[1],
                            ego_driven_distance,
                            seconds);
    compute_future_distance(vehicles.vehicles_right_lane[0],
                            ego_driven_distance,
                            seconds);
    compute_future_distance(vehicles.vehicles_right_lane[1],
                            ego_driven_distance,
                            seconds);
}

#include <chrono>
#include <cstring>
#include <iostream>
#include <numeric>
#include <thread>

#include "AdFunctions.hpp"
#include "AdTypes.hpp"

#include "utils.hpp"

namespace fs = std::filesystem;

int main(int argc, char **argv)
{
    auto data_filepath = fs::path{};

    if (argc < 2) //wenn keine Argumente übergeben werden
    {
        data_filepath /= fs::current_path();
        data_filepath /= "data";
    }
    else
    {
        const auto user_path_str = std::string(argv[1]);
        data_filepath = fs::path(user_path_str);
    }

    auto ego_data_path = data_filepath;
    ego_data_path /= "ego_data.json";
    auto vehicle_data_path = data_filepath;
    vehicle_data_path /= "vehicle_data.json";

    auto ego_vehicle = VehicleType{};
    auto vehicles = NeighborVehiclesType{};

    init_ego_vehicle(ego_vehicle);
    init_vehicles(vehicles);

    print_vehicle(ego_vehicle);
    print_neighbor_vehicles(vehicles);

    std::cout << "Start simulation?: ";
    auto Input = char{};
    std::cin >> Input;

    while (true)
    {
        clear_console();

        print_scene(ego_vehicle, vehicles);
        compute_future_state(ego_vehicle, vehicles, 0.100F);

        const auto ego_lane_vehicles =
            get_vehicle_array(ego_vehicle.lane, vehicles);
        longitudinal_control(ego_lane_vehicles[0], ego_vehicle);

        const auto lane_change_request =
            get_lane_change_request(ego_vehicle, vehicles);
        const auto lane_change_executed =
            lateral_control(lane_change_request, ego_vehicle);

        if (lane_change_executed)
        {
            printf("Executed lane change!");
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}

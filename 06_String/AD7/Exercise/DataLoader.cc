#include <fstream>
#include <vector>

#include "AdTypes.hpp"
#include "DataLoader.hpp"
#include "DataLoaderConstants.hpp"
#include "DataLoaderTypes.hpp"

static VehiclesData vehicles_data = std::vector<std::vector<VehicleType>>(
    NUM_VEHICLES,
    std::vector<VehicleType>(NUM_ITERATIONS));

void init_ego_vehicle(std::string_view filepath, VehicleType &ego_vehicle)
{
    std::ifstream ifs("ego_data.json");
    json parsed_data = json::parse(ifs);

    ego_vehicle.id = EGO_VEHICLE_ID;
    ego_vehicle.distance_m = 0.0F;
    ego_vehicle.speed_mps = static_cast<float>(parsed_data["Speed"]);
    ego_vehicle.lane = static_cast<LaneAssociationType>(parsed_data["Lane"]);


}

void init_vehicles(std::string_view filepath, NeighborVehiclesType &vehicles)
{
    std::ifstream ifs("ego_data.json");
    json parsed_data = json::parse(ifs);

    for (std::size_t vehicle_index = 0; vehicle_index < NUM_VEHICLES; vehicle_index++)
    {
        //Iterieren über die 6 verschiedenen Fahrzeuge (Nr. 0-5)
            //Fahrzeug-Nummer MUSS als String übergeben werden -> 1 Nummer = 1 Abschnitt
        const auto &vehicle_data = parsed_data[std::to_string(vehicle_index)];

        //Auslesen von ID, Lane und Distance aus dem jeweiligen "Fahrzeugkapitel"
        const auto id = static_cast<std::int32_t>(vehicle_data);
        const auto lane = static_cast<LaneAssociationType>(vehicle_data["Lane"]);
        const auto distance_m = static_cast<float>(vehicle_data["Distance"]);

        //Iterieren über 1000 Frames, um alle Geschwindigkeiten abzuspeichern
        for (std::size_t it = 0; it < NUM_ITERATIONS; it++)
        {
            const auto speed = static_cast<float>(vehicle_data["Speed"][it]);

            //Abspeichern der Fahrzeugdaten in die vehicles_data Struktur
            vehicles_data[vehicle_index][it] = {.id = id, .lane = lane, .speed_mps = speed, .distance_m = distance_m};
        }

    }

    //Fahrzeugzustände im ersten Zyklus vor-laden [vehicle_index][Zyklus]
    vehicles.vehicles_left_lane[0] = vehicles_data[0][0];
    vehicles.vehicles_left_lane[1] = vehicles_data[1][0];
    vehicles.vehicles_center_lane[0] = vehicles_data[2][0];
    vehicles.vehicles_center_lane[1] = vehicles_data[3][0];
    vehicles.vehicles_right_lane[0] = vehicles_data[4][0];
    vehicles.vehicles_right_lane[1] = vehicles_data[5][0];

}

void load_cycle(const std::uint32_t cycle, NeighborVehiclesType &vehicles)
{
    vehicles.vehicles_left_lane[0].speed_mps = vehicles_data[0][cycle].speed_mps;
    vehicles.vehicles_left_lane[1].speed_mps = vehicles_data[1][cycle].speed_mps;
    vehicles.vehicles_center_lane[0].speed_mps = vehicles_data[2][cycle].speed_mps;
    vehicles.vehicles_center_lane[1].speed_mps = vehicles_data[3][cycle].speed_mps;
    vehicles.vehicles_right_lane[0].speed_mps = vehicles_data[4][cycle].speed_mps;
    vehicles.vehicles_right_lane[1].speed_mps = vehicles_data[5][cycle].speed_mps;

}

#pragma once

#include "AirConditioner.h"

enum class AcStates {
    IDLE,
    COOLING,
    HEATING,
};

class AcStateMachine
{
public:
    AcStateMachine() = default;
    AcStateMachine(AirConditioner *const _ac_) : ac(_ac_){};
    ~AcStateMachine() = default;

    void evaluation(const float curr_temp_cel);
    AcStates get_state();

private:
    AirConditioner *const ac = nullptr;
    AcStates state = AcStates::IDLE;

    void eval_transition(const float curr_temp_cel);
    void eval_state(const float curr_temp_cel);
};

#include "AcStateMachine.h"

void AcStateMachine::eval_state(const float curr_temp_cel)
{
    switch (state)
    {
    case AcStates::HEATING:
    case AcStates::COOLING:
        ac->activate(curr_temp_cel);

    case AcStates::IDLE:
    default:
        break;
    }

}

void AcStateMachine::eval_transition(const float curr_temp_cel)
{
    auto target_temp = ac->get_target_temp_cel();
    if (curr_temp_cel == target_temp)
        state = AcStates::IDLE;
    else if (curr_temp_cel > target_temp)
        state = AcStates::COOLING;
    else
        state = AcStates::HEATING;
}

void AcStateMachine::evaluation(const float curr_temp_cel)
{
    eval_state(curr_temp_cel);
    eval_transition(curr_temp_cel);
}

AcStates AcStateMachine::get_state()
{
    return state;
}

#include "SimClock.h"

SimClock::SimClock(float fixedTimestep) : fixedTimestep_(fixedTimestep), accumulator_(0.0f) {}

void SimClock::tick(float deltaTime)
{
    accumulator_ += deltaTime;
}

bool SimClock::shouldStepPhysics()
{
    if (accumulator_ >= fixedTimestep_)
    {
        accumulator_ -= fixedTimestep_;
        return true;
    }
    return false;
}

float SimClock::getFixedTimestep()
{
    return fixedTimestep_;
}

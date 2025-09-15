#include "SimClock.h"

/**
 * @brief Construct a simulation clock with a fixed timestep.
 *
 * Initializes the clock with the specified fixed timestep and resets
 * the accumulator to zero.
 *
 * @param fixedTimestep The fixed time step for physics simulation in seconds
 */
SimClock::SimClock(float fixedTimestep) : fixedTimestep_(fixedTimestep), accumulator_(0.0f) {}

/**
 * @brief Advance the simulation clock by the given delta time.
 *
 * This method accumulates the real time that has passed, which will be
 * used to determine when physics steps should occur.
 *
 * @param deltaTime Time elapsed since the last tick in seconds
 */
void SimClock::tick(float deltaTime)
{
    accumulator_ += deltaTime;
}

/**
 * @brief Check if a physics step should be performed.
 *
 * This implements the fixed timestep logic. If enough time has accumulated
 * (at least one fixed timestep), it consumes that time and returns true.
 * This ensures physics simulation runs at a consistent rate.
 *
 * @return true if physics should step, false otherwise
 */
bool SimClock::shouldStepPhysics()
{
    if (accumulator_ >= fixedTimestep_)
    {
        accumulator_ -= fixedTimestep_;
        return true;
    }
    return false;
}

/**
 * @brief Get the fixed timestep value.
 *
 * Returns the fixed timestep that was set during construction.
 *
 * @return The fixed timestep in seconds
 */
float SimClock::getFixedTimestep()
{
    return fixedTimestep_;
}

#ifndef SIMCLOCK_H
#define SIMCLOCK_H

/**
 * @brief Simulation clock for managing fixed timestep physics updates.
 *
 * The SimClock implements a fixed timestep system for physics simulation,
 * accumulating real time and determining when physics steps should occur.
 * This ensures consistent physics behavior regardless of frame rate.
 */
class SimClock
{
public:
    /**
     * @brief Construct a simulation clock with a fixed timestep.
     *
     * @param fixedTimestep The fixed time step for physics simulation in seconds
     */
    SimClock(float fixedTimestep);

    /**
     * @brief Advance the simulation clock by the given delta time.
     *
     * Adds the delta time to the accumulator, which tracks how much time
     * has passed since the last physics step.
     *
     * @param deltaTime Time elapsed since the last tick in seconds
     */
    void tick(float deltaTime);

    /**
     * @brief Check if a physics step should be performed.
     *
     * Returns true if enough time has accumulated for a physics step.
     * If true, the accumulated time is reduced by one fixed timestep.
     *
     * @return true if physics should step, false otherwise
     */
    bool shouldStepPhysics();

    /**
     * @brief Get the fixed timestep value.
     *
     * @return The fixed timestep in seconds
     */
    float getFixedTimestep();

private:
    float fixedTimestep_; /**< The fixed time step for physics simulation */
    float accumulator_;   /**< Accumulated time since last physics step */
};

#endif

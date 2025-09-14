#ifndef SIMCLOCK_H
#define SIMCLOCK_H

class SimClock
{
public:
    SimClock(float fixedTimestep);
    void tick(float deltaTime);
    bool shouldStepPhysics();
    float getFixedTimestep();

private:
    float fixedTimestep_;
    float accumulator_;
};

#endif

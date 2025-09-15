#ifndef IMPULSECOLLISIONRESOLVER_H
#define IMPULSECOLLISIONRESOLVER_H

#include "ICollisionResolver.h"

class ImpulseCollisionResolver : public ICollisionResolver {
public:
    ImpulseCollisionResolver(float friction, float restitution);
    void resolveCollision(float& vx, float& vy, float& vz, float normalX, float normalY, float normalZ, float restitution) override;
private:
    float friction_;
    float restitution_;
};

#endif

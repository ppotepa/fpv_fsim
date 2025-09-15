#ifndef ICOLLISIONRESOLVER_H
#define ICOLLISIONRESOLVER_H

class ICollisionResolver {
public:
    virtual ~ICollisionResolver() = default;
    virtual void resolveCollision(float& vx, float& vy, float& vz, float normalX, float normalY, float normalZ, float restitution) = 0;
};

#endif

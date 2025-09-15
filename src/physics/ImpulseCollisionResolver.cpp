#include "ImpulseCollisionResolver.h"

ImpulseCollisionResolver::ImpulseCollisionResolver(float friction, float restitution)
    : friction_(friction), restitution_(restitution) {}

void ImpulseCollisionResolver::resolveCollision(float &vx, float &vy, float &vz, float normalX, float normalY, float normalZ, float restitution)
{
    // Stub: simple impulse
    float dot = vx * normalX + vy * normalY + vz * normalZ;
    if (dot < 0)
    {
        vx -= (1 + restitution) * dot * normalX;
        vy -= (1 + restitution) * dot * normalY;
        vz -= (1 + restitution) * dot * normalZ;
    }
}

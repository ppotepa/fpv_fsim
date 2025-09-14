#ifndef ISYSTEM_H
#define ISYSTEM_H

class World;

class ISystem
{
public:
    virtual ~ISystem() = default;
    virtual void update(World &amp; world, float dt) = 0;
};

#endif

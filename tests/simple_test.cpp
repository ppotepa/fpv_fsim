#include <iostream>

namespace EntityFactory
{
    class EntityFactory
    {
    public:
        EntityFactory() = default;
    };
}

int main()
{
    EntityFactory::EntityFactory test;
    DEBUG_LOG("Test passed");
    return 0;
}

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
    std::cout << "Test passed" << std::endl;
    return 0;
}

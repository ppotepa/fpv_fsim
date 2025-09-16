#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

bool Debug()
{
#ifdef DEBUG
    return true;
#else
    return false;
#endif
}

#endif

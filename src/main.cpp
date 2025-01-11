#include "graphics.hpp"


int main()
{
    Graphics graphics;

    if (!graphics.init()) return -1;

    if (!graphics.loadMedia()) return -1;

    graphics.run();

    graphics.cleanup();

    return 0;
}
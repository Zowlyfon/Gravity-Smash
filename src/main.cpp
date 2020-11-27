#include <iostream>
#include "Engine.h"

int main()
{
    Engine engine(1920, 1080);
    engine.init();
    engine.run();
    return 0;
}

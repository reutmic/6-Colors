#include "Window.h"
#include <cstdlib>
#include <ctime>

int main() {
    unsigned seed = std::time(nullptr);
    std::srand(seed);

    Window window;
    window.run();

    return 0;
}

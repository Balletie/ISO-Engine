#include "window.h"

int main(int, char const**) {
    if (window::open() == EXIT_FAILURE) return EXIT_FAILURE;
    window::loop();
    return EXIT_SUCCESS;
}

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ResourcePath.hpp"
#include "tile.h"
#include "world.h"

using namespace std;
using namespace sf;

bool load_textures(tex* tex) {
    if(!(tex->grass   .loadFromFile(resourcePath() + "grass.png")    &&
         tex->water   .loadFromFile(resourcePath() + "water.png")    &&
         tex->sand    .loadFromFile(resourcePath() + "sand.png")     &&
         tex->building.loadFromFile(resourcePath() + "building.png") &&
         tex->shallow .loadFromFile(resourcePath() + "shallow.png")  )) {
        return false;
    }
    return true;
}

int main(int, char const**) {
    tex textures;

    if (!load_textures(&textures)) {
        return EXIT_FAILURE;
    }

    World world(&textures);
    RenderWindow window(VideoMode(world.dimension * 64, world.dimension * 32), "ISO-Engine");

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                window.close();
            }
        }
        window.clear();
        world.draw(window);
        window.display();
    }
    return EXIT_SUCCESS;
}
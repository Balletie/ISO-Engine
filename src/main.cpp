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
        for (int i = 0; i < world.dimension; i++) {
            for (int j = world.dimension - 1; j >= 0; j--) {
                tile current = world.world_data[i*10 + j];
                Sprite sp = world.getSprite(current);

                int x = (window.getSize().x/2 - 10 * 64 / 2) + World::rowcol_to_x(i,j);
                int y = (window.getSize().y/2 - 16)          + World::rowcol_to_y(i,j);

                if (y - current.y_offset < 0) {
                    sp.setTextureRect(IntRect(0, current.y_offset,64,32));
                    sp.setColor(Color(255,200,200));
                    current.y_offset = 0;
                }

                sp.setPosition(x, y - current.y_offset);
                window.draw(sp);
            }
        }
        window.display();
    }
    return EXIT_SUCCESS;
}
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

void handle_keys(RenderWindow& window, float dt) {
    if(Keyboard::isKeyPressed(Keyboard::Left)) {
        View temp = window.getView();
        temp.move(-2 * dt/1000, 0);
        window.setView(temp);
    }
    if(Keyboard::isKeyPressed(Keyboard::Right)) {
        View temp = window.getView();
        temp.move(2 * dt/1000, 0);
        window.setView(temp);
    }
    if(Keyboard::isKeyPressed(Keyboard::Up)) {
        View temp = window.getView();
        temp.move(0, -2 * dt/1000);
        window.setView(temp);
    }
    if(Keyboard::isKeyPressed(Keyboard::Down)) {
        View temp = window.getView();
        temp.move(0, 2 * dt/1000);
        window.setView(temp);
    }
}

int main(int, char const**) {
    tex textures;

    if (!load_textures(&textures)) {
        return EXIT_FAILURE;
    }

    World world(&textures);
    RenderWindow window(VideoMode(world.dimension * 64, world.dimension * 32), "ISO-Engine");

    Clock clock;
    while (window.isOpen()) {
        Time elapsed = clock.restart();
        Event event;
        handle_keys(window, elapsed.asMicroseconds());
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::KeyPressed) {
                switch(event.key.code) {
                    case Keyboard::Escape:
                        window.close();
                        break;
                    case Keyboard::Num0:
                        window.setView(window.getDefaultView());
                        break;
                    default:
                        break;
                }
            }
        }
        window.clear();
        world.draw(window);
        window.display();
    }
    return EXIT_SUCCESS;
}
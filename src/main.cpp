#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#if defined(SFML_SYSTEM_MACOS)
    #include "ResourcePath.hpp"
#endif
#include "tile.h"
#include "world.h"

using namespace std;

bool load_textures(tex* tex) {
    if (!(tex->grass   .loadFromFile(resourcePath() + "grass.png")    &&
          tex->water   .loadFromFile(resourcePath() + "water.png")    &&
          tex->sand    .loadFromFile(resourcePath() + "sand.png")     &&
          tex->building.loadFromFile(resourcePath() + "building.png") &&
          tex->shallow .loadFromFile(resourcePath() + "shallow.png")  )) {
        return false;
    }
    return true;
}

void handle_keys(sf::RenderWindow& window, float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sf::View temp = window.getView();
        temp.move(-2 * dt/1000, 0);
        window.setView(temp);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sf::View temp = window.getView();
        temp.move(2 * dt/1000, 0);
        window.setView(temp);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        sf::View temp = window.getView();
        temp.move(0, -2 * dt/1000);
        window.setView(temp);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        sf::View temp = window.getView();
        temp.move(0, 2 * dt/1000);
        window.setView(temp);
    }
}

int main(int, char const**) {
    tex textures;

    if (!load_textures(&textures)) {
        return EXIT_FAILURE;
    }

    World world(textures);
    sf::RenderWindow window(sf::VideoMode(world.dimension * 64, world.dimension * 32), "ISO-Engine");
    window.setFramerateLimit(60);

    sf::View middleView = window.getDefaultView();
    middleView.move(0, -((int)window.getSize().y)/2 + 16);
    window.setView(middleView);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        handle_keys(window, dt.asMicroseconds());

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                switch (event.mouseButton.button) {
                    case sf::Mouse::Left:{
                        sf::Vector2f coord = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        int row = xy_to_row(coord.x, coord.y, 32);
                        int col = xy_to_col(coord.x, coord.y, 32);
                        world.world_data[0].layer_data[row][col].texture = &(world.texture_data.sand);
                        break;
                    }
                    default:
                        break;
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::Num0:
                        window.setView(middleView);
                        break;
                    case sf::Keyboard::Z:{
                        sf::View temp = window.getView();
                        temp.zoom(0.8);
                        window.setView(temp);
                        break;
                    }
                    case sf::Keyboard::X:{
                        sf::View temp = window.getView();
                        temp.zoom(1.2);
                        window.setView(temp);
                        break;
                    }
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
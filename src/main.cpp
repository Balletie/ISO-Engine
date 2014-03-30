#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#if defined(SFML_SYSTEM_MACOS)
    #include "OSX/ResourcePath.hpp"
#elif defined(SFML_SYSTEM_LINUX)
    #define resourcePath() std::string("assets/")
#endif
#include "tile.h"
#include "transforms.h"
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

void handle_keys(sf::RenderTexture& texture, float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sf::View temp = texture.getView();
        temp.move(-2 * dt/1000, 0);
        texture.setView(temp);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sf::View temp = texture.getView();
        temp.move(2 * dt/1000, 0);
        texture.setView(temp);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        sf::View temp = texture.getView();
        temp.move(0, -2 * dt/1000);
        texture.setView(temp);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        sf::View temp = texture.getView();
        temp.move(0, 2 * dt/1000);
        texture.setView(temp);
    }
}

int main(int, char const**) {
    tex textures;

    if (!load_textures(&textures)) {
        return EXIT_FAILURE;
    }

    World world(textures, 50, 50);
    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "ISO-Engine", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    sf::RenderTexture texture;
    texture.create(window.getSize().x, window.getSize().y);

    sf::View middleView = texture.getDefaultView();
    middleView.move(-((int)texture.getSize().x/2 - 10 * 64 / 2), -((int)texture.getSize().y)/2 + 16);
    texture.setView(middleView);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        handle_keys(texture, dt.asMicroseconds());

        sf::Event event;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2f coord = texture.mapPixelToCoords(sf::Mouse::getPosition(window));
            int row = standardxy_to_isoy(coord.x, coord.y, 32);
            int col = standardxy_to_isox(coord.x, coord.y, 32);
            world.world_data[0][row][col] = {&(world.texture_data.sand), 31};
        }
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::Num0:
                        texture.setView(middleView);
                        break;
                    case sf::Keyboard::Z:{
                        sf::View temp = texture.getView();
                        temp.zoom(0.8);
                        texture.setView(temp);
                        break;
                    }
                    case sf::Keyboard::X:{
                        sf::View temp = texture.getView();
                        temp.zoom(1.2);
                        texture.setView(temp);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
        texture.clear();
        world.draw(texture);
        texture.display();

        sf::Sprite sprite(texture.getTexture());

        window.clear();
        window.draw(sprite);
        window.display();
    }
    return EXIT_SUCCESS;
}

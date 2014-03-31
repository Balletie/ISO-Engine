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
#include "highlight.h"
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
    sf::RenderWindow window(sf::VideoMode(1280, 640), "ISO-Engine");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    sf::RenderTexture texture;
    texture.create(window.getSize().x, window.getSize().y);

    sf::Clock clock;
    Highlighter highlight(0, 0);

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        handle_keys(texture, dt.asMicroseconds());

        sf::Event event;
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
                        texture.setView(texture.getDefaultView());
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
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if(!highlight.active) {
                        sf::Vector2f coord = texture.mapPixelToCoords(sf::Mouse::getPosition(window));
                        highlight.x0 = coord.x;
                        highlight.y0 = coord.y;
                        highlight.active = true;
                    } else {
                        highlight.active = false;
                    }
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    sf::Vector2f coord = texture.mapPixelToCoords(sf::Mouse::getPosition(window));
                    int row = xy_to_tile_y(coord.x, coord.y, 32);
                    int col = xy_to_tile_x(coord.x, coord.y, 32);
                    world.world_data[0][row][col] = {&(world.texture_data.sand), 31};
                }
            }
        }
        texture.clear();
        world.draw(texture);
        if (highlight.active) {
            sf::Vector2f coord = texture.mapPixelToCoords(sf::Mouse::getPosition(window));
            sf::VertexArray selection = highlight(coord.x, coord.y);
            texture.draw(selection);
        }
        texture.display();

        sf::Sprite sprite(texture.getTexture());

        window.clear();
        window.draw(sprite);
        window.display();
    }
    return EXIT_SUCCESS;
}

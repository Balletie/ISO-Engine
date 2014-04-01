//
//  window.cpp
//  iso-engine
//
//  Created by Skip Lentz on 01/04/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#include "window.h"
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

namespace window {
    namespace {
        sf::Clock clock;
        sf::RenderWindow window;
        sf::RenderTexture cache;
        Highlighter highlight;
        tex textures;
        World world(textures, 50, 50);

        void input() {
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
                            cache.setView(cache.getDefaultView());
                            break;
                        case sf::Keyboard::Z:{
                            sf::View temp = cache.getView();
                            temp.zoom(0.8);
                            cache.setView(temp);
                            break;
                        }
                        case sf::Keyboard::X:{
                            sf::View temp = cache.getView();
                            temp.zoom(1.2);
                            cache.setView(temp);
                            break;
                        }
                        default:
                            break;
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if(!highlight.active) {
                            sf::Vector2f coord = cache.mapPixelToCoords(sf::Mouse::getPosition(window));
                            highlight.x0 = coord.x;
                            highlight.y0 = coord.y;
                            highlight.active = true;
                        } else {
                            highlight.active = false;
                        }
                    } else if (event.mouseButton.button == sf::Mouse::Right) {
                        sf::Vector2f coord = cache.mapPixelToCoords(sf::Mouse::getPosition(window));
                        int row = xy_to_tile_y(coord.x, coord.y, 32);
                        int col = xy_to_tile_x(coord.x, coord.y, 32);
                        world.world_data[0][row][col] = {&(world.texture_data.sand), 31};
                    }
                }
            }
        }
        void handle_keys(float dt) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                sf::View temp = cache.getView();
                temp.move(-2 * dt/1000, 0);
                cache.setView(temp);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                sf::View temp = cache.getView();
                temp.move(2 * dt/1000, 0);
                cache.setView(temp);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                sf::View temp = cache.getView();
                temp.move(0, -2 * dt/1000);
                cache.setView(temp);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                sf::View temp = cache.getView();
                temp.move(0, 2 * dt/1000);
                cache.setView(temp);
            }
        }
        bool load_textures(tex& tex) {
            if (!(tex.grass   .loadFromFile(resourcePath() + "grass.png")    &&
                  tex.water   .loadFromFile(resourcePath() + "water.png")    &&
                  tex.sand    .loadFromFile(resourcePath() + "sand.png")     &&
                  tex.building.loadFromFile(resourcePath() + "building.png") &&
                  tex.shallow .loadFromFile(resourcePath() + "shallow.png")  )) {
                return false;
            }
            return true;
        }
    }

    int open() {
        window.create(sf::VideoMode::getFullscreenModes()[0], "ISO-Engine", sf::Style::Fullscreen);
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(60);
        if (!cache.create(window.getSize().x, window.getSize().y))  return EXIT_FAILURE;
        if (!load_textures(textures))                               return EXIT_FAILURE;
        loop();
        return EXIT_SUCCESS;
    }

    void loop() {
        while (window.isOpen()) {
            sf::Time dt = clock.restart();
            handle_keys(dt.asMicroseconds());
            input();

            cache.clear();
            world.draw(cache);
            if (highlight.active) {
                sf::Vector2f coord = cache.mapPixelToCoords(sf::Mouse::getPosition(window));
                sf::VertexArray selection = highlight(coord.x, coord.y);
                cache.draw(selection);
            }
            cache.display();
            sf::Sprite sprite(cache.getTexture());

            window.clear();
            window.draw(sprite);
            window.display();
        }
    }
}
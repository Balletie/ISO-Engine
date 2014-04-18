//
//  window.cpp
//  iso-engine
//
//  Created by Skip Lentz on 01/04/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#include "window.h"

namespace window {
    namespace {
        sf::Clock clock;
        sf::RenderWindow window;
        Highlighter highlight;
        World world(100, 100);

        void handle_keys() {
            float dt = clock.restart().asMicroseconds();
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

        void handle_input() {
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
                            window.setView(window.getDefaultView());
                            break;
                        case sf::Keyboard::Z:{
                            sf::View temp = window.getView();
                            temp.zoom(0.5);
                            window.setView(temp);
                            break;
                        }
                        case sf::Keyboard::X:{
                            sf::View temp = window.getView();
                            temp.zoom(2);
                            window.setView(temp);
                            break;
                        }
                        default:
                            break;
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if(!highlight.active) {
                            sf::Vector2f coord = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                            highlight.x0 = coord.x;
                            highlight.y0 = coord.y;
                            highlight.active = true;
                        } else {
                            highlight.active = false;
                        }
                    } else if (event.mouseButton.button == sf::Mouse::Right) {
                        sf::Vector2f coord = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        int row = xy_to_tile_y(coord.x, coord.y, 32);
                        int col = xy_to_tile_x(coord.x, coord.y, 32);
                        world.select(0, row, col);
                    }
                }
            }
        }

        void update() {
            handle_keys();
            handle_input();
        }

        void draw() {
            window.clear();
            window.draw(world);
            if (highlight.active) {
                sf::Vector2f coord = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                window.draw(highlight(coord.x, coord.y));
            }
            window.display();
        }
    }

    int open() {
        window.create(sf::VideoMode(1280, 786), "ISO-Engine", sf::Style::Close | sf::Style::Titlebar);
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(60);
        if (!load_textures())       return EXIT_FAILURE;
        if (!world.createCache())   return EXIT_FAILURE;
        world.addLayer(100, 100); world.fillLayer(0, {GRASS});
        return EXIT_SUCCESS;
    }

    void loop() {
        while (window.isOpen()) {
            update();
            draw();
        }
    }
}
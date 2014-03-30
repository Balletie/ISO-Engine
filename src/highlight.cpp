//
//  highlight.cpp
//  iso-engine
//
//  Created by Skip Lentz on 30/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#include "highlight.h"
#include <iostream>

Highlighter::Highlighter(float x, float y) : x0(x)
                                           , y0(y)
                                           , active(false)
{}

sf::VertexArray Highlighter::operator()(float x, float y) {
    sf::VertexArray selection(sf::Quads, 4);
    float tempx0 = xy_to_tile_x(x0,y0,2);
    float tempy0 = xy_to_tile_y(x0,y0,2);
    float tempx = xy_to_tile_x(x, y, 2);
    float tempy = xy_to_tile_y(x, y, 2);
    selection[0].position = sf::Vector2f(x0, y0);
    selection[1].position = sf::Vector2f(tile_xy_to_x(tempx, tempy0, 2), tile_xy_to_y(tempx, tempy0, 2));
    selection[2].position = sf::Vector2f(x, y);
    selection[3].position = sf::Vector2f(tile_xy_to_x(tempx0, tempy, 2), tile_xy_to_y(tempx0, tempy, 2));
    selection[0].color = sf::Color::Red;
    selection[1].color = sf::Color::Blue;
    selection[2].color = sf::Color::Green;
    selection[3].color = sf::Color::Yellow;
    return selection;
}
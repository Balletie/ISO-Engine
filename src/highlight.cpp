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

sf::VertexArray Highlighter::operator()(float x1, float y1) {
    sf::VertexArray selection(sf::Quads, 4);
    float tilex0 = xy_to_tile_x(x0, y0, 2);
    float tiley0 = xy_to_tile_y(x0, y0, 2);
    float tilex1 = xy_to_tile_x(x1, y1, 2);
    float tiley1 = xy_to_tile_y(x1, y1, 2);
    selection[0].position = sf::Vector2f(x0, y0);
    selection[1].position = sf::Vector2f(tile_xy_to_x(tilex0, tiley1, 2), -tile_xy_to_y(tilex0, tiley1, 2));
    selection[2].position = sf::Vector2f(x1, y1);
    selection[3].position = sf::Vector2f(tile_xy_to_x(tilex1, tiley0, 2), -tile_xy_to_y(tilex1, tiley0, 2));
    for (int i = 0; i < 4; i++) {
        selection[i].color.a = 175;
    }
    return selection;
}


//
//  world.cpp
//  iso-engine
//
//  Created by Skip Lentz on 01/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#include "world.h"
#include <iostream>
#include <algorithm>
using sf::Sprite;
using sf::Color;

World::World(tex* tex_data) : texture_data(tex_data), dimension(10) {
    tile gr = {&(tex_data->grass),27};

    std::fill(world_data.begin(), world_data.end(), gr);
    world_data[0] = {&(tex_data->shallow),32};
    world_data[1] = {&(tex_data->shallow),32};
    world_data[2] = {&(tex_data->building), 32};
    world_data[11] = {&(tex_data->shallow),32};
    world_data[12] = {&(tex_data->shallow),32};
    world_data[13] = {&(tex_data->shallow),32};
    world_data[23] = {&(tex_data->shallow),32};
    world_data[33] = {&(tex_data->shallow),32};
    world_data[22] = {&(tex_data->sand),30};
    world_data[67] = {&(tex_data->sand),30};
    world_data[68] = {&(tex_data->sand),30};
}

Sprite World::getSprite(tile a) {
    return Sprite(*a.texture);
}

int World::rowcol_to_x(int row, int col) {
    return col * 32 + row * 32;
}

int World::rowcol_to_y(int row, int col) {
    return row * 16 - col * 16;
}
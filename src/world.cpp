//
//  world.cpp
//  iso-engine
//
//  Created by Skip Lentz on 01/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#include "world.h"
#include <iostream>

World::World(tex& tex_data, int x, int y) : texture_data(tex_data)
                                          , x(x), y(y)
                                          , world_data(1, Layer(x, y))
{
    world_data[0].fill({&(texture_data.grass), 27});
    newLayer(20, 10);
    world_data[1].fill({&(texture_data.sand), 32});
}

sf::Sprite World::getSprite(tile a) {
    return a.texture != nullptr ? sf::Sprite(*a.texture) : sf::Sprite();
}

void World::newLayer(int x, int y) {
    if (x > this->x) this->x = x;
    if (y > this->y) this->y = y;
    world_data.push_back(Layer(x, y));
}

void World::draw(sf::RenderTexture& texture) {
    for (int i = 0; i < x; i++) {
        for (int j = y - 1; j >= 0; j--) {
            for (int l = 0; l < world_data.size(); l++) {
                if (i >= world_data[l].size())    continue;
                if (j >= world_data[l][i].size()) continue;
                tile current    = this->world_data[l][i][j];
                int tile_height = this->world_data[l].tile_height;
                sf::Sprite sp   = this->getSprite(current);

                int x = tile::rowcol_to_x(i,j, tile_height);
                int y = tile::rowcol_to_y(i,j, tile_height);

                sp.setPosition(x, y - current.y_offset);
                texture.draw(sp);
            }
        }
    }
}

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
    addLayer(20, 10, 44);
    world_data[1].fill({&(texture_data.building), 40});
    world_data[0][30][10] = {&(texture_data.sand), 31};
}

sf::Sprite World::getSprite(tile a) {
    return a.texture != nullptr ? sf::Sprite(*a.texture) : sf::Sprite();
}

void World::addLayer(int x, int y, int height) {
    if (x > this->x) this->x = x;
    if (y > this->y) this->y = y;
    world_data.push_back(Layer(x, y, height));
}

void World::draw(sf::RenderTexture& texture) {
    for (int l = 0; l < world_data.size(); l++) {
        for (int i = 0; i < world_data[l].size(); i++) {
            for (int j = world_data[l][i].size() - 1; j >= 0; j--) {
                tile current    = this->world_data[l][i][j];
                int tile_height = this->world_data[l].tile_height;
                sf::Sprite sp   = this->getSprite(current);

                int x = tile_xy_to_x(i,j, tile_height);
                int y = tile_xy_to_y(i,j, tile_height);

                sp.setPosition(x, y - current.y_offset);
                texture.draw(sp);
            }
        }
    }
}

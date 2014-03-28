//
//  world.cpp
//  iso-engine
//
//  Created by Skip Lentz on 01/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#include "world.h"

World::World(tex& tex_data) : texture_data(tex_data)
                            , world_data(1, Layer(10, 10))
                            , dimension(10)
{
    world_data[0].fill({&(texture_data.grass), 27});
    world_data.push_back(Layer(10, 10));
    world_data[1][3][3] = {&(texture_data.building), 40};
}

sf::Sprite World::getSprite(tile a) {
    return a.texture != nullptr ? sf::Sprite(*a.texture) : sf::Sprite();
}

void World::draw(sf::RenderWindow& window) {
    for (int i = 0; i < dimension; i++) {
        for (int j = dimension - 1; j >= 0; j--) {
            for (int l = 0; l < world_data.size(); l++) {
                tile current    = this->world_data[l][i][j];
                int tile_height = this->world_data[l].tile_height;
                sf::Sprite sp   = this->getSprite(current);

                int x = rowcol_to_x(i,j, tile_height);
                int y = rowcol_to_y(i,j, tile_height);

                sp.setPosition(x, y - current.y_offset);
                window.draw(sp);
            }
        }
    }
}
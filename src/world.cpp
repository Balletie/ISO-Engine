//
//  world.cpp
//  iso-engine
//
//  Created by Skip Lentz on 01/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#include "world.h"

World::World(tex& tex_data) : texture_data(tex_data)
                            //next line creates one layer, initialized with grass tiles
                            , world_data(1, {std::vector<std::vector<tile>>(10, std::vector<tile>(10,{&(texture_data.grass), 27})), 32, 64})
                            , dimension(10)
{
    std::vector<std::vector<tile>> temp(10, std::vector<tile>(10));
    temp[3][3] = {&(texture_data.building), 40};
    temp[4][3] = {&(texture_data.building), 40};
    temp[5][3] = {&(texture_data.building), 40};
    world_data.push_back({temp, 32, 64});
}

sf::Sprite World::getSprite(tile a) {
    return a.texture != nullptr ? sf::Sprite(*a.texture) : sf::Sprite();
}

void World::draw(sf::RenderWindow& window){
    for (int i = 0; i < this->dimension; i++) {             //for each row i
        for (int j = this->dimension - 1; j >= 0; j--) {    //for each column j
            for (int l = 0; l < world_data.size(); l++) {   //for each layer
                tile current    = this->world_data[l].layer_data[i][j];
                int tile_width  = this->world_data[l].tile_width;
                int tile_height = this->world_data[l].tile_height;
                sf::Sprite sp   = this->getSprite(current);

                int x = (window.getSize().x/2 - 10 * 64 / 2) + rowcol_to_x(i,j, tile_width);
                int y = (window.getSize().y/2 - 16)          + rowcol_to_y(i,j, tile_height);

                sp.setPosition(x, y - current.y_offset);
                window.draw(sp);
            }
        }
    }
}
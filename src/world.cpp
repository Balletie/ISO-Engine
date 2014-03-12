//
//  world.cpp
//  iso-engine
//
//  Created by Skip Lentz on 01/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#include "world.h"
#include <iostream>

World::World(tex& tex_data) : texture_data(tex_data),
                              world_data(100, {
                                                &(texture_data.grass),  //The texture address
                                                27                      //The y_offset
                                              }),
                              dimension(10)
{}

sf::Sprite World::getSprite(tile a) {
    return a.texture != nullptr ? sf::Sprite(*a.texture) : sf::Sprite();
}

void World::draw(sf::RenderWindow& window){
    for (int i = 0; i < this->dimension; i++) {
        for (int j = this->dimension - 1; j >= 0; j--) {
            tile current = this->world_data[i*10 + j];
            sf::Sprite sp = this->getSprite(current);

            int x = (window.getSize().x/2 - 10 * 64 / 2) + rowcol_to_x(i,j);
            int y = (window.getSize().y/2 - 16)          + rowcol_to_y(i,j);

            sp.setPosition(x, y - current.y_offset);
            window.draw(sp);
        }
    }
}

int World::rowcol_to_x(int row, int col) {
    return col * 32 + row * 32;
}

int World::rowcol_to_y(int row, int col) {
    return row * 16 - col * 16;
}
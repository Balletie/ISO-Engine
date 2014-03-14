//
//  tile.h
//  iso-engine
//
//  Created by Skip Lentz on 01/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#ifndef iso_engine_tile_h
#define iso_engine_tile_h

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

struct tex {
    sf::Texture grass, water, shallow, sand, rock, building;
};

struct tile {
    sf::Texture* texture;
    int y_offset;
};

int rowcol_to_x(int, int, int);
int rowcol_to_y(int, int, int);
#endif

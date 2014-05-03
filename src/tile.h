//
//  tile.h
//  iso-engine
//
//  Created by Skip Lentz on 03/04/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#ifndef __iso_engine__tile__
#define __iso_engine__tile__
#include <SFML/Graphics/Texture.hpp>
#include <vector>

extern std::vector<sf::Texture> tilesets;

enum tile_type : uint8_t {
    UNKNOWN = 0,

    GRASS,
    SAND,
    SHALLOW,
    WATER,
    NUM_NATURE,

    ONE_STORY,
    TWO_STORY,
    NUM_BUILDINGS
};

enum tileset {
    NATURE,
    BUILDINGS
};

struct tile {
    tile_type   type;
    int         y_offset;
};

bool load_tilesets();

#endif /* defined(__iso_engine__tile__) */

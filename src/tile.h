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
#include <string>
#if defined(SFML_SYSTEM_MACOS)
    #include "OSX/ResourcePath.hpp"
#elif defined(SFML_SYSTEM_LINUX)
    #define resourcePath() std::string("assets/")
#endif

extern std::vector<sf::Texture> texture_data;

enum tile_type {
    UNKNOWN,
    GRASS,
    WATER,
    SHALLOW,
    SAND,
    BUILDING,
    NUM_TYPES
};

struct tile {
    tile_type type;
    int y_offset;
};

bool load_textures();

#endif /* defined(__iso_engine__tile__) */

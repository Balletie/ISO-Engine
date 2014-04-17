//
//  tile.cpp
//  iso-engine
//
//  Created by Skip Lentz on 03/04/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#include "tile.h"
#if defined(SFML_SYSTEM_MACOS)
    #include "OSX/ResourcePath.hpp"
#elif defined(SFML_SYSTEM_LINUX)
    #include <string>
    #define resourcePath() std::string("assets/")
#endif

std::vector<sf::Texture> texture_data(5);

bool load_textures() {
    if (!(texture_data[GRASS]    .loadFromFile(resourcePath() + "grass.png")    &&
          texture_data[WATER]    .loadFromFile(resourcePath() + "water.png")    &&
          texture_data[SAND]     .loadFromFile(resourcePath() + "sand.png")     &&
          texture_data[BUILDING] .loadFromFile(resourcePath() + "building.png") &&
          texture_data[SHALLOW]  .loadFromFile(resourcePath() + "shallow.png")  &&
          texture_data[NUM_TYPES].loadFromFile(resourcePath() + "tileset.png"))) {
        return false;
    }
    return true;
}
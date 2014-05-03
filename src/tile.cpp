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

std::vector<sf::Texture> tilesets(2);

bool load_tilesets() {
    bool success = false;
    success |= tilesets[NATURE]   .loadFromFile(resourcePath() + "nature.png");
    success &= tilesets[BUILDINGS].loadFromFile(resourcePath() + "buildings.png");
    return success;
}
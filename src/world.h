//
//  world.h
//  iso-engine
//
//  Created by Skip Lentz on 01/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#ifndef __iso_engine__world__
#define __iso_engine__world__

#include <array>
#include "tile.h"
using namespace std;

class World {
  public:
    tex* texture_data;
    const int dimension;
    array<tile, 100> world_data;
    World(tex*);
    sf::Sprite getSprite(tile);
    static int rowcol_to_x(int, int);
    static int rowcol_to_y(int, int);
};

#endif /* defined(__iso_engine__world__) */

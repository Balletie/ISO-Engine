//
//  layer.h
//  iso-engine
//
//  Created by Skip Lentz on 12/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#ifndef __iso_engine__layer__
#define __iso_engine__layer__

#include "tile.h"

struct layer {
    std::vector<std::vector<tile> > layer_data;
    int tile_height;
};

#endif /* defined(__iso_engine__layer__) */

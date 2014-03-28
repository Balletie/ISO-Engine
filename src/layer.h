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

class Layer {
  private:
    std::vector<std::vector<tile> > layer_data;
  public:
    const int tile_height;
    Layer(int, int, int height = 32);
    void fill(tile t);
    std::vector<tile>& operator [](int i);
    std::vector<tile>  operator [](int i) const;
};

#endif /* defined(__iso_engine__layer__) */

//
//  tile.cpp
//  iso-engine
//
//  Created by Skip Lentz on 13/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#include "tile.h"

int tile::rowcol_to_x(int row, int col, int height) {
    return row * height + col * height;
}

int tile::rowcol_to_y(int row, int col, int height) {
    return row * height/2 - col * height/2 - height/2;
}

int tile::xy_to_row(float x, float y, float height) {
    return (int)(y / height + x / (2 * height));
}

int tile::xy_to_col(float x, float y, float height) {
    return (int)(x / (2 * height) - y / height);
}
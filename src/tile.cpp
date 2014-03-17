//
//  tile.cpp
//  iso-engine
//
//  Created by Skip Lentz on 13/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#include "tile.h"

int rowcol_to_x(int row, int col, int width) {
    return col * width/2 + row * width/2;
}

int rowcol_to_y(int row, int col, int height) {
    return row * height/2 - col * height/2;
}

int xy_to_row(float x, float y, int height) {
    return (int)((y - height/2) / height + (x - height/2) / (2 * height));
}

int xy_to_col(float x, float y, int height) {
    return (int)((x - height/2) / (2 * height) - (y - height/2) / height);
}
//
//  transforms.cpp
//  iso-engine
//
//  Created by Skip Lentz on 30/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#include "transforms.h"

float tile_xy_to_x(float row, float col, float height) {
    return row * height + col * height;
}

float tile_xy_to_y(float row, float col, float height) {
    return row * height/2 - col * height/2 - height/2;
}

int xy_to_tile_y(float x, float y, float height) {
    return (int)(y / height + x / (2 * height));
}

int xy_to_tile_x(float x, float y, float height) {
    return (int)(x / (2 * height) - y / height);
}
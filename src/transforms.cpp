//
//  transforms.cpp
//  iso-engine
//
//  Created by Skip Lentz on 30/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#include "transforms.h"

float tile_xy_to_x(float x, float y, float height) {
    return x * height + y * height;
}

float tile_xy_to_y(float x, float y, float height) {
    return -x * height/2 + y * height/2 - height/2;
}

float xy_to_tile_x(float x, float y, float height) {
    return x / (2 * height) + y / height;
}

float xy_to_tile_y(float x, float y, float height) {
    return x / (2 * height) - y / height;
}
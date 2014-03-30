//
//  transforms.cpp
//  iso-engine
//
//  Created by Skip Lentz on 30/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#include "transforms.h"

int isoxy_to_standardx(int row, int col, int height) {
    return row * height + col * height;
}

int isoxy_to_standardy(int row, int col, int height) {
    return row * height/2 - col * height/2 - height/2;
}

int standardxy_to_isoy(float x, float y, float height) {
    return (int)(y / height + x / (2 * height));
}

int standardxy_to_isox(float x, float y, float height) {
    return (int)(x / (2 * height) - y / height);
}
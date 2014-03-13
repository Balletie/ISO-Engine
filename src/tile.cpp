//
//  tile.cpp
//  iso-engine
//
//  Created by Skip Lentz on 13/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#include "tile.h"

int rowcol_to_x(int row, int col) {
    return col * 32 + row * 32;
}

int rowcol_to_y(int row, int col) {
    return row * 16 - col * 16;
}
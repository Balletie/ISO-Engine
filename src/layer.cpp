//
//  layer.cpp
//  iso-engine
//
//  Created by Skip Lentz on 12/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#include "layer.h"

Layer::Layer(int x, int y, int height) : layer_data(std::vector< std::vector<tile> >(x, std::vector<tile>(y,{UNKNOWN, 0})))
                                       , tile_height(height)
{}

void Layer::fill(tile t) {
    for (int i = 0; i < layer_data.size(); i++) {
        for (int j = 0; j < layer_data[i].size(); j++) {
            layer_data[i][j] = t;
        }
    }
}

int Layer::size() {
    return layer_data.size();
}

void Layer::set(int row, int col, tile t) {
    if (row >= layer_data.size())       return;
    if (col >= layer_data[row].size())  return;
    layer_data[row][col] = t;
}

std::vector<tile>& Layer::operator[](int i) {
    return layer_data[i];
}

std::vector<tile>  Layer::operator[](int i) const {
    return layer_data[i];
}
//
//  world.cpp
//  iso-engine
//
//  Created by Skip Lentz on 01/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#include "world.h"
#include <iostream>

World::World(int x1, int y1)
    : x(x1 * 64)
    , y(y1 * 32)
{}

sf::Sprite World::getCache() {
    sf::Sprite sprite(cache.getTexture());
    sprite.move(0, -this->y / 2);
    return sprite;
}

bool World::createCache() {
    bool success = cache.create(2048, 2048);
    cache.clear();
    cache.draw(*this);
    cache.display();
    return success;
}

void World::loadWorld(std::string infile) {
    sf::Image img;
    img.loadFromFile(infile);
    int sizex = img.getSize().x;
    int sizey = img.getSize().y;
    const uint8_t* pixels = img.getPixelsPtr();
    this->world_data = std::vector<Layer>(4,Layer(sizex, sizey, NATURE, 32));
    for (int i = 0; i<sizex; i++) {
        for (int j = 0; j<sizey; j++) {
            for (int k = 0; k<3; k++) {
                tile_type t = static_cast<tile_type>(pixels[i*sizex*4+j*4+k]/(255/NUM_NATURE));
                this->world_data[k].set(i,j,{t});
            }
        }
    }
}

bool World::saveWorld(std::string infile) {
    sf::Image img;
    unsigned int sizex = x/64;
    unsigned int sizey = y/32;
    uint8_t* pixels = new uint8_t[sizex*sizey*4];
    for (int i = 0; i<sizex; i++) {
        for (int j = 0; j<sizey; j++) {
            for (int k = 0; k<3; k++) {
                if (k<world_data.size()) {
                    pixels[i*sizex*4+j*4+k] = world_data[k].get(i,j).type*(255/NUM_NATURE);
                } else {
                    pixels[i*sizex*4+j*4+k] = 0;    //Must be set to zero, undefined behaviour otherwise
                }
            }
            pixels[i*sizex*4+j*4+3] = 255;
        }
    }
    img.create(sizex, sizey, pixels);
    delete [] pixels;
    return img.saveToFile(infile);
}

void World::addLayer(int x, int y, tileset set, int height) {
    if (x * 2 * height > this->x)   this->x = x * 2 * height;
    if (y * height> this->y)        this->y = y * height;
    world_data.push_back(Layer(x, y, set, height));
}

void World::fillLayer(int layer, tile t) {
    if (layer < 0 || layer >= world_data.size()) {
        return;
    }
    world_data[layer].fill(t);
}

void World::set(int layer, int row, int col, tile t) {
    if (layer < 0 || layer >= world_data.size()) return;
    world_data[layer].set(row, col, t);
    cache.clear();
    cache.draw(*this);
    cache.display();
}

void World::select(int layer, int row, int col) {
    if (layer < 0 || layer >= world_data.size()) return;
    world_data[layer].select(row, col);
    cache.clear();
    cache.draw(*this);
    cache.display();
}

void World::selectRange(int layer, int start_row, int start_col, int end_row, int end_col) {
    if (layer < 0 || layer >= world_data.size()) return;
    world_data[layer].selectRange(start_row, start_col, end_row, end_col);
    cache.clear();
    cache.draw(*this);
    cache.display();
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int l = 0; l < world_data.size(); l++) {
        target.draw(world_data[l]);
    }
}
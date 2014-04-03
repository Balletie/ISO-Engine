//
//  world.cpp
//  iso-engine
//
//  Created by Skip Lentz on 01/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#include "world.h"

namespace {
    sf::RenderTexture cache;
}

World::World(int x, int y) : x(x * 64), y(y * 32)
                           , world_data(1, Layer(x, y))
{
    world_data[0].fill({GRASS, 27});
    addLayer(20, 10, 44);
    world_data[1].fill({BUILDING, 40});
    world_data[0][30][10] = {SAND, 31};
}

sf::Sprite World::getSprite(tile a) {
    if (a.type == UNKNOWN)        return sf::Sprite();
    else if (a.type >= NUM_TYPES) return sf::Sprite();
    else                          return sf::Sprite(texture_data[a.type]);
}

sf::Sprite World::getCache() {
    sf::Sprite sprite(cache.getTexture());
    sprite.move(0, -this->y / 2);
    return sprite;
}

bool World::createCache() {
    bool success = cache.create(2048, 2048);
    this->draw();
    return success;
}

void World::addLayer(int x, int y, int height) {
    if (x * 2 * height > this->x)   this->x = x * 2 * height;
    if (y * height> this->y)        this->y = y * height;
    world_data.push_back(Layer(x, y, height));
}

void World::set(int layer, int row, int col, tile t) {
    if (layer < 0 || layer >= world_data.size()) return;
    world_data[layer].set(row, col, t);
    this->draw();
}

void World::draw() {
    cache.clear();
    for (int l = 0; l < world_data.size(); l++) {
        for (int i = 0; i < world_data[l].size(); i++) {
            for (int j = world_data[l][i].size() - 1; j >= 0; j--) {
                tile current    = this->world_data[l][i][j];
                int tile_height = this->world_data[l].tile_height;
                sf::Sprite sp   = this->getSprite(current);

                int coordx = tile_xy_to_x(i,j, tile_height);
                int coordy = tile_xy_to_y(i,j, tile_height);

                sp.setPosition(coordx, coordy - current.y_offset + y/2);
                cache.draw(sp);
            }
        }
    }
    cache.display();
}

Layer& World::operator [](int i) {
    return world_data[i];
}

Layer World::operator [](int i) const {
    return world_data[i];
}
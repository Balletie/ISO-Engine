//
//  world.cpp
//  iso-engine
//
//  Created by Skip Lentz on 01/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#include "world.h"

World::World(int x1, int y1) : x(x1 * 64)
                             , y(y1 * 32)
{}

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
    cache.clear();
    cache.draw(*this);
    cache.display();
    return success;
}

void World::addLayer(int x, int y, int height) {
    if (x * 2 * height > this->x)   this->x = x * 2 * height;
    if (y * height> this->y)        this->y = y * height;
    world_data.push_back(Layer(x, y, texture_data[NUM_TYPES], height));
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

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int l = 0; l < world_data.size(); l++) {
        target.draw(world_data[l]);
    }
}
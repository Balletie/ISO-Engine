//
//  world.h
//  iso-engine
//
//  Created by Skip Lentz on 01/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#ifndef __iso_engine__world__
#define __iso_engine__world__

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include "layer.h"
#include "transforms.h"

class World {
  public:
    int x;
    int y;
    std::vector<Layer> world_data;

    World(int, int);
    void addLayer(int, int, int height = 32);
    void draw(sf::RenderTexture& texture);

  private:
    sf::Sprite getSprite(tile);
};

#endif /* defined(__iso_engine__world__) */

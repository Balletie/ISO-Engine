//
//  world.h
//  iso-engine
//
//  Created by Skip Lentz on 01/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#ifndef __iso_engine__world__
#define __iso_engine__world__

#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "layer.h"

class World {
  public:
    tex& texture_data;
    const int dimension;
    std::vector<Layer> world_data;
    World(tex&);
    void draw(sf::RenderWindow& window);

  private:
    sf::Sprite getSprite(tile);
};

#endif /* defined(__iso_engine__world__) */

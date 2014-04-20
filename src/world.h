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

class World : public sf::Drawable {
  public:
    int x;
    int y;

    World(int, int);
    void addLayer(int, int, int height = 32);
    void fillLayer(int, tile);
    void set(int, int, int, tile);
    void select(int, int, int);
    void selectRange(int, int, int, int, int);
    sf::Sprite getCache();
    bool createCache();

  private:
    sf::RenderTexture cache;
    std::vector<Layer> world_data;
    sf::Sprite getSprite(tile);

  protected:
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};

#endif /* defined(__iso_engine__world__) */

//
//  layer.h
//  iso-engine
//
//  Created by Skip Lentz on 12/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#ifndef __iso_engine__layer__
#define __iso_engine__layer__

#include "tile.h"
#include "transforms.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Shader.hpp>

class Layer : public sf::Drawable {
    friend class World;

  private:
    int x;
    int y;
    std::shared_ptr<sf::Shader> sel;
    sf::Texture                 tilemap;
    sf::VertexArray             layer_vertices;

  public:
    const int tile_height;

    Layer(int, int, sf::Texture, int height = 32);
    void fill(tile t);
    int size();
    void loadShader();
    void set(int, int, tile);
    void select(int, int);
    void selectRange(int, int, int ,int);

  protected:
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
    void setTilemap(sf::Texture);
};

#endif /* defined(__iso_engine__layer__) */

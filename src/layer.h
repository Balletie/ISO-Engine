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
    const int x;
    const int y;
    std::shared_ptr<sf::Shader>     sel;
    tileset                         tset;
    sf::VertexArray                 layer_vertices;
    std::vector<std::vector<tile>>  layer_tiles;

  public:
    const int tile_height;

    Layer(int, int, tileset, int height = 32);
    void fill(tile t);
    int size();
    void loadShader();

    tile get(int, int);
    void set(int, int, tile);
    void select(int, int);
    void selectRange(int, int, int ,int);

  protected:
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
    void setTilemap(sf::Texture);
};

#endif /* defined(__iso_engine__layer__) */

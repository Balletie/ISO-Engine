//
//  layer.cpp
//  iso-engine
//
//  Created by Skip Lentz on 12/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#include "layer.h"

Layer::Layer(int x, int y, tileset tiles, int height)
    : x(x), y(y)
    , layer_vertices(sf::Quads, 4*x*y)
    , layer_tiles(x,std::vector<tile>(y))
    , tset(tiles)
    , tile_height(height)
    , sel(new sf::Shader)
{
    std::string frag =  \
    "uniform sampler2D texture;"\
    "void main(){"\
    "    vec4 tex = texture2D(texture, gl_TexCoord[0].xy);"\
    "    float rgb = max(tex.r,max(tex.g, tex.b));"\
    "    if(gl_Color.a > 0.0){"\
    "        gl_FragColor = tex;"\
    "    }else{"\
    "        gl_FragColor = tex.a * vec4(rgb+.2, rgb+.2, rgb+.2, 1.0);"\
    "    }"\
    "}";
    sel->loadFromMemory(frag, sf::Shader::Fragment);
    sel->setParameter("texture", sf::Shader::CurrentTexture);
}

void Layer::fill(tile t) {
    for (int i = 0; i<x; i++) {
        for (int j = 0; j<y; j++) {
            this->set(i, j, t);
        }
    }
}

int Layer::size() {
    return layer_vertices.getVertexCount()/4;
}

tile Layer::get(int i, int j) {
    return layer_tiles[i][j];
}

void Layer::set(int i, int j, tile t) {
    layer_tiles[i][j] = t;

    uint8_t type = t.type;
    if (tset == BUILDINGS) type -= NUM_NATURE;

    int u = (type - 1) % (tilesets[tset].getSize().x/(2*tile_height));
    int v = (type - 1) / (tilesets[tset].getSize().x/(2*tile_height));
    int coordx = tile_xy_to_x(i, j, tile_height);
    int coordy = tile_xy_to_y(i, j, tile_height);

    sf::Vertex* quad = &layer_vertices[(x-i-1+j*x)*4];

    quad[0].position = sf::Vector2f(coordx,                 coordy - t.y_offset);
    quad[1].position = sf::Vector2f(coordx + 2*tile_height, coordy - t.y_offset);
    quad[2].position = sf::Vector2f(coordx + 2*tile_height, coordy - t.y_offset + 2*tile_height);
    quad[3].position = sf::Vector2f(coordx,                 coordy - t.y_offset + 2*tile_height);

    quad[0].color = sf::Color::Black;
    quad[1].color = sf::Color::Black;
    quad[2].color = sf::Color::Black;
    quad[3].color = sf::Color::Black;

    if (type != UNKNOWN) {
        quad[0].texCoords = sf::Vector2f(u*tile_height*2,v*tile_height*2);
        quad[1].texCoords = sf::Vector2f((u+1)*tile_height*2,v*tile_height*2);
        quad[2].texCoords = sf::Vector2f((u+1)*tile_height*2,(v+1)*tile_height*2);
        quad[3].texCoords = sf::Vector2f(u*tile_height*2, (v+1)*tile_height*2);
    }
}

void Layer::select(int i, int j) {
    sf::Vertex* quad = &layer_vertices[(x-i-1+j*x)*4];
    for (int i = 0; i < 4; i++) {
            quad[i].color.a = 0;
    }
}

void Layer::selectRange(int start_row, int start_col, int end_row, int end_col) {
    int dif1 = end_col - start_col;
    int dif2 = end_row - start_row;
    if (dif1 > 0) end_col = start_col; else dif1 *= -1;
    if (dif2 > 0) end_row = start_row; else dif2 *= -1;
    for (int row = 0; row <= dif2; row++) {
        for (int col = 0; col <= dif1; col++) {
            select(row+end_row,col+end_col);
        }
    }
}

void Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.texture = &tilesets[tset];
    states.shader = sel.get();
    target.draw(layer_vertices, states);
}
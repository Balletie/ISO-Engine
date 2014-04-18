//
//  layer.cpp
//  iso-engine
//
//  Created by Skip Lentz on 12/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#include "layer.h"

Layer::Layer(int x, int y, sf::Texture tilemap, int height)
    : x(x), y(y)
    , layer_vertices(sf::VertexArray(sf::Quads, 4*x*y))
    , tilemap(tilemap)
    , tile_height(height)
{}

void Layer::fill(tile t) {
    for (int i = x - 1; i>=0; i--) {
        for (int j = 0; j < y; j++) {
            this->set(i, j, t);
        }
    }
}

int Layer::size() {
    return layer_vertices.getVertexCount()/4;
}

void Layer::set(int i, int j, tile t) {
    int u = t.type%(tilemap.getSize().x/(2*tile_height));
    int v = t.type/(tilemap.getSize().x/(2*tile_height));
    int coordx = tile_xy_to_x(i, j, tile_height);
    int coordy = tile_xy_to_y(i, j, tile_height);
    sf::Vertex* quad = &layer_vertices[(x-i-1+j*x)*4];

    quad[0].position = sf::Vector2f(coordx, coordy);
    quad[1].position = sf::Vector2f(coordx + 2*tile_height, coordy);
    quad[2].position = sf::Vector2f(coordx + 2*tile_height, coordy + 2*tile_height);
    quad[3].position = sf::Vector2f(coordx, coordy + 2*tile_height);

    quad[0].color = sf::Color::Black;
    quad[1].color = sf::Color::Black;
    quad[2].color = sf::Color::Black;
    quad[3].color = sf::Color::Black;

    quad[0].texCoords = sf::Vector2f(u*tile_height*2,v*tile_height*2);
    quad[1].texCoords = sf::Vector2f((u+1)*tile_height*2,v*tile_height*2);
    quad[2].texCoords = sf::Vector2f((u+1)*tile_height*2,(v+1)*tile_height*2);
    quad[3].texCoords = sf::Vector2f(u*tile_height*2, (v+1)*tile_height*2);
}

void Layer::select(int i, int j) {
    sf::Vertex* quad = &layer_vertices[(x-i-1+j*x)*4];
    for (int i = 0; i < 4; i++) {
            quad[i].color = sf::Color::White;
            quad[i].color.a = 0;
    }
}

void Layer::setTilemap(sf::Texture t) {
    this->tilemap = t;
}

void Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.texture = &tilemap;
    sf::Shader shader;
    std::string frag = \
    "uniform sampler2D texture;"\
    "void main(){"\
    "   vec4 tex = texture2D(texture, gl_TexCoord[0].xy);"\
    "   vec4 outColor = tex + tex.a * gl_Color;"\
    "   gl_FragColor = outColor * vec4(1.0,1.0,1.0,0.5);"\
    "}";
    shader.loadFromMemory(frag, sf::Shader::Fragment);
    shader.setParameter("texture", sf::Shader::CurrentTexture);
    states.shader = &shader;
    target.draw(layer_vertices, states);
}
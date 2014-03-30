//
//  highlight.h
//  iso-engine
//
//  Created by Skip Lentz on 30/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#ifndef __iso_engine__highlight__
#define __iso_engine__highlight__

#include <SFML/Graphics/VertexArray.hpp>
#include "transforms.h"

struct Highlighter {
public:
    bool active;
    float x0, y0;
    Highlighter(float, float);
    sf::VertexArray operator()(float, float);
};

#endif /* defined(__iso_engine__highlight__) */

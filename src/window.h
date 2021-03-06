//
//  window.h
//  iso-engine
//
//  Created by Skip Lentz on 01/04/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#ifndef __iso_engine__window__
#define __iso_engine__window__
#include <SFML/Graphics.hpp>
#include "transforms.h"
#include "highlight.h"
#include "world.h"

namespace window {
    int open();
    void loop();
};

#endif /* defined(__iso_engine__window__) */

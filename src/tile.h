//
//  tile.h
//  iso-engine
//
//  Created by Skip Lentz on 01/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#ifndef iso_engine_tile_h
#define iso_engine_tile_h

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

struct tex {
    sf::Texture grass, water, shallow, sand, rock, building;
};

struct tile {
    sf::Texture* texture;
    int y_offset;
};

/////////////////////////////////////////////////
/// \brief Convert to standard basis
///
/// Using the following matrix transformation:
///
/// [  h    h  ] [ row ] -> [ x ]
/// [ h/2 -h/2 ] [ col ] -> [ y ]
///
/// The column vectors form the isometric basis
/// representing the coordinate system.
///
/// \see rowcol_to_y
/////////////////////////////////////////////////
int rowcol_to_x(int, int, int);
int rowcol_to_y(int, int, int);

/////////////////////////////////////////////////
/// \brief Convert to isometric basis
///
/// Using the following matrix transformation:
///
/// [ 1/2h  1/h ] [ x ] -> [ row ]
/// [ 1/2h -1/h ] [ y ] -> [ col ]
///
/// This matrix is the inverse of the previous
/// matrix.
///
/// \see xy_to_row
/////////////////////////////////////////////////
int xy_to_col(float, float, float);
int xy_to_row(float, float, float);
#endif

//
//  transforms.h
//  iso-engine
//
//  Created by Skip Lentz on 30/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#ifndef __iso_engine__transforms__
#define __iso_engine__transforms__

#include <SFML/System/Vector2.hpp>

/////////////////////////////////////////////////
/// \brief The isometric x-axis vector.
/////////////////////////////////////////////////
const sf::Vector2f b1 = sf::Vector2f(2,  1);

/////////////////////////////////////////////////
/// \brief The isometric y-axis vector.
/////////////////////////////////////////////////
const sf::Vector2f b2 = sf::Vector2f(2,  -1);

/////////////////////////////////////////////////
/// \brief Convert to standard basis
///
/// Using the following matrix transformation:
///
/// [   h    h  ] [ x1 ] -> [ x ]
/// [ -h/2  h/2 ] [ y1 ] -> [ y ]
///
/// The column vectors form the isometric basis
/// representing the coordinate system.
///
/// \see tile_xy_to_x
/////////////////////////////////////////////////
float tile_xy_to_x(float, float, float);
float tile_xy_to_y(float, float, float);

/////////////////////////////////////////////////
/// \brief Convert to isometric basis
///
/// Using the following matrix transformation:
///
/// [ 1/2h  1/h ] [ x1 ] -> [ x ]
/// [ 1/2h -1/h ] [ y1 ] -> [ y ]
///
/// This matrix is the inverse of the previous
/// matrix.
///
/// \see xy_to_tile_y
/////////////////////////////////////////////////
float xy_to_tile_x(float, float, float);
float xy_to_tile_y(float, float, float);


#endif /* defined(__iso_engine__transforms__) */

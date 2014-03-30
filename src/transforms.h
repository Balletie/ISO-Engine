//
//  transforms.h
//  iso-engine
//
//  Created by Skip Lentz on 30/03/14.
//  Copyright (c) 2014 ___bal___. All rights reserved.
//

#ifndef __iso_engine__transforms__
#define __iso_engine__transforms__

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
int isoxy_to_standardx(int, int, int);
int isoxy_to_standardy(int, int, int);

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
int standardxy_to_isox(float, float, float);
int standardxy_to_isoy(float, float, float);


#endif /* defined(__iso_engine__transforms__) */

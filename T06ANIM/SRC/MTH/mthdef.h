/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : mthdef.h
 * PURPOSE     : Math base definitions.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#ifndef __mthdef_h_
#define __mthdef_h_
#include <commondf.h>
#include <cmath>

/* Math namespace */
namespace mth
{
  /* Math constant 'pi' */
  #define PI 3.14159265358979323846

  /* Convert degrees to radians */
  #define D2R(A) ((A) / 180.0 * PI)

  /* Get max value */
  #define MAX(A, B) ((A) > (B) ? (A) : (B))

  /* Get min value */
  #define MIN(A, B) ((A) < (B) ? (A) : (B))

  template<class Type> class vec3;
  template<class Type> class matr;
} /* End of 'mth' namespace */

typedef DOUBLE DBL;
typedef FLOAT FLT;

#endif /* __mthdef_h_ */

/* END OF 'mthdef.h' */

/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : mth_vec3.h
 * PURPOSE     : Math vec3 definitions.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#ifndef __mth_vec3_h_
#define __mth_vec3_h_

#include "mthdef.h"
#include <cstdlib>
#include <math.h>

/* Space math namespace */
namespace mth
{
  /* 3D vector representation type */
  template<class Type>
    class vec3
    {
    private:
      Type X, Y, Z;
    public:
      template<class OtherType>
        friend class matr;

      /* Constructor function.
       * ARGUMENTS: None.
       */
      vec3( VOID ) : X(0), Y(0), Z(0)
      {
      } /* End of 'vec3' function */

      /* Constructor function.
       * ARGUMENTS:
       *   - vec coords:
       *       Type X, Y, Z;
       */
      vec3( Type X, Type Y, Type Z ) : X(X), Y(Y), Z(Z)
      {
      } /* End of 'vec3' function */

      /* Constructor function.
       * ARGUMENTS:
       *   - vec coord:
       *       Type a;
       */
      vec3( Type a ) : X(a), Y(a), Z(a)
      {
      } /* End of 'vec3' function */

      /* Operator '+' redefenition function.
       * ARGUMENTS:
       *   - other vec:
       *       const vec3 &v;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator+( const vec3 &v ) const
      {
        return vec3(X + v.X, Y + v.Y, Z + v.Z);
      } /* End of 'operator+' function */

      /* Operator '+' redefenition function.
       * ARGUMENTS:
       *   - other vec:
       *       const vec3 &v;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator-( const vec3 &v ) const
      {
        return vec3(X - v.X, Y - v.Y, Z - v.Z);
      } /* End of 'operator-' function */

      /* Operator '*' redefenition function.
       * ARGUMENTS:
       *   - other vec:
       *       const vec3 &v;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator*( const vec3 &v ) const
      {
        return vec3(X * v.X, Y * v.Y, Z * v.Z);
      } /* End of 'operator*' function */

      /* Operator '*' redefenition function.
       * ARGUMENTS:
       *   - number:
       *       const Type num;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator*( const Type &n ) const
      {
        return vec3(X * n, Y * n, Z * n);
      } /* End of 'operator*' function */

      /* Operator '/' redefenition function.
       * ARGUMENTS:
       *   - number:
       *       const Type num;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator/( const Type &n ) const
      {
        return vec3(X / n, Y / n, Z / n);
      } /* End of 'operator/' function */

      /* Operator '!' redefenition function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) result.
       */
      Type operator!( VOID ) const
      {
        return sqrt(X * X + Y * Y + Z * Z);
      } /* End of 'operator!' function */

      /* Operator '&' redefenition function.
       * ARGUMENTS:
       *   - other vec:
       *       const vec3 &v;
       * RETURNS:
       *   (Type) result.
       */
      Type operator&( const vec3 &v ) const
      {
        return X * v.X + Y * v.Y + Z * v.Z;
      } /* End of 'operator&' function */

      /* Operator '%' redefenition function.
       * ARGUMENTS:
       *   - other vec:
       *       const vec3 &v;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator%( const vec3 &v ) const
      {
        return vec3(Y * v.Z - Z * v.Y, Z * v.X - X * v.Z, X * v.Y - Y * v.X);
      } /* End of 'operator%' function */

      /* Operator '+=' redefenition function.
       * ARGUMENTS:
       *   - other vec:
       *       const vec3 &v;
       * RETURNS:
       *   (vec3 &) result vector.
       */
      vec3 & operator+=( const vec3 &v )
      {
        X += v.X, Y += v.Y, Z += v.Z;

        return *this;
      } /* End of 'operator+=' function */

      /* Operator '-=' redefenition function.
       * ARGUMENTS:
       *   - other vec:
       *       const vec3 &v;
       * RETURNS:
       *   (vec3 &) result vector.
       */
      vec3 & operator-=( const vec3 &v )
      {
        X -= v.X, Y -= v.Y, Z -= v.Z;

        return *this;
      } /* End of 'operator-=' function */

      /* Operator '*=' redefenition function.
       * ARGUMENTS:
       *   - other vec:
       *       const vec3 &v;
       * RETURNS:
       *   (vec3 &) result vector.
       */
      vec3 & operator*=( const vec3 &v )
      {
        X *= v.X, Y *= v.Y, Z *= v.Z;

        return *this;
      } /* End of 'operator*=' function */

      /* Operator '*=' redefenition function.
       * ARGUMENTS:
       *   - number:
       *       const Type &n;
       * RETURNS:
       *   (vec3 &) result vector.
       */
      vec3 & operator*=( const Type &n )
      {
        X *= n, Y *= n, Z *= n;

        return *this;
      } /* End of 'operator*=' function */

      /* Operator '/=' redefenition function.
       * ARGUMENTS:
       *   - number:
       *       const Type &n;
       * RETURNS:
       *   (vec3 &) result vector.
       */
      vec3 & operator/=( const Type &n )
      {
        X /= n, Y /= n, Z /= n;

        return *this;
      } /* End of 'operator/=' function */

      /* Normalize vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3 &) result vector.
       */
      vec3 & Normalize( VOID )
      {
        Type length = !*this;

        if (length == 0)
          X = Y = Z = 0;
        else
          X /= length, Y /= length, Z /= length;

        return *this;
      } /* End of 'Normalize' function */

      /* Normalize vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 Normalizing( VOID ) const
      {
        Type length = !*this;

        if (length == 0)
          return Zero();

        return vec3(X / length, Y / length, Z / length);
      } /* End of 'Normalizing' function */

      /* Get length square of vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) result.
       */
      Type Length2( VOID ) const
      {
        return X * X + Y * Y + Z * Z;
      } /* End of 'Length2' function */

      /* Get distance to point function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) result.
       */
      Type Distance( const vec3 &P ) const
      {
        return !(*this - P);
      } /* End of 'Distance' function */

      /* Get null vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) result vector.
       */
      static vec3 Zero( VOID )
      {
        return vec3(0);
      } /* End of 'Zero' function */

      /* Get vector with random coords from 0 to 1 function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) result vector.
       */
      static vec3 Rnd0( VOID )
      {
        return vec3(rand() / (Type)RAND_MAX, rand() / (Type)RAND_MAX, rand() / (Type)RAND_MAX);
      } /* End of 'Rnd0' function */

      /* Get vector with random coords from -1 to 1 function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) result vector.
       */
      static vec3 Rnd1( VOID )
      {
        return vec3(rand() * 2 / (Type)RAND_MAX - 1, rand() * 2 / (Type)RAND_MAX - 1, rand() * 2 / (Type)RAND_MAX - 1);
      } /* End of 'Rnd1' function */

      /* Operator '[]' redefenition function.
       * ARGUMENTS:
       *   - index:
       *       const int &i;
       * RETURNS:
       *   (Type &) coord link.
       */
      Type & operator[]( const int &i )
      {
        if (i == 0)
          return X;
        else if (i == 1)
          return Y;
        else
          return Z;
      } /* End of 'operator[]' function */

      /* Operator '[]' redefenition function.
       * ARGUMENTS:
       *   - index:
       *       const int &i;
       * RETURNS:
       *   (Type) coord.
       */
      Type operator[]( const int &i ) const
      {
        if (i == 0)
          return X;
        else if (i == 1)
          return Y;
        else
          return Z;
      } /* End of 'operator[]' function */

      /* Operator 'Type *' redefenition function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type *) pointer to first coord.
       */
      operator Type *( VOID )
      {
        return &X;
      } /* End of 'operator Type *' function */

    }; /* End of 'vec3' class */
} /* end of 'mth' namespace */

#endif /* __mth_vec3_h_ */

/* END OF 'mth_vec3.h' FILE */

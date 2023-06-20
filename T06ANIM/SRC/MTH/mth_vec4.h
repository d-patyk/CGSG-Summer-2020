/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : mth_vec4.h
 * PURPOSE     : Math vec4 definitions.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#ifndef __mth_vec4_h_
#define __mth_vec4_h_

#include "mthdef.h"
#include <cstdlib>
#include <math.h>

/* Space math namespace */
namespace mth
{
  /* 4D vector representation type */
  template<class Type>
    class vec4
    {
    private:
      Type X, Y, Z, W;
    public:
      template<class OtherType>
        friend class matr;

      /* Constructor function.
       * ARGUMENTS: None.
       */
      vec4( VOID ) : X(0), Y(0), Z(0), W(0)
      {
      } /* End of 'vec4' function */

      /* Constructor function.
       * ARGUMENTS:
       *   - vec coords:
       *       Type X, Y, Z, W;
       */
      vec4( Type X, Type Y, Type Z, Type W ) : X(X), Y(Y), Z(Z), W(W)
      {
      } /* End of 'vec4' function */

      /* Constructor function.
       * ARGUMENTS:
       *   - vec coord:
       *       Type a;
       */
      vec4( Type a ) : X(a), Y(a), Z(a), W(a)
      {
      } /* End of 'vec4' function */

      /* Operator '+' redefenition function.
       * ARGUMENTS:
       *   - other vec:
       *       const vec4 &v;
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 operator+( const vec4 &v ) const
      {
        return vec4(X + v.X, Y + v.Y, Z + v.Z, W + v.W);
      } /* End of 'operator+' function */

      /* Operator '+' redefenition function.
       * ARGUMENTS:
       *   - other vec:
       *       const vec4 &v;
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 operator-( const vec4 &v ) const
      {
        return vec4(X - v.X, Y - v.Y, Z - v.Z, W - v.W);
      } /* End of 'operator-' function */

      /* Operator '*' redefenition function.
       * ARGUMENTS:
       *   - other vec:
       *       const vec4 &v;
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 operator*( const vec4 &v ) const
      {
        return vec4(X * v.X, Y * v.Y, Z * v.Z, W * v.W);
      } /* End of 'operator*' function */

      /* Operator '*' redefenition function.
       * ARGUMENTS:
       *   - number:
       *       const Type num;
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 operator*( const Type &n ) const
      {
        return vec4(X * n, Y * n, Z * n, W * n);
      } /* End of 'operator*' function */

      /* Operator '/' redefenition function.
       * ARGUMENTS:
       *   - number:
       *       const Type num;
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 operator/( const Type &n ) const
      {
        return vec4(X / n, Y / n, Z / n, W / n);
      } /* End of 'operator/' function */

      /* Operator '!' redefenition function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) result.
       */
      Type operator!( VOID ) const
      {
        return sqrt(X * X + Y * Y + Z * Z + W * W);
      } /* End of 'operator!' function */

      /* Operator '&' redefenition function.
       * ARGUMENTS:
       *   - other vec:
       *       const vec4 &v;
       * RETURNS:
       *   (Type) result.
       */
      Type operator&( const vec4 &v ) const
      {
        return X * v.X + Y * v.Y + Z * v.Z + W * v.W;
      } /* End of 'operator&' function */

      /* Operator '+=' redefenition function.
       * ARGUMENTS:
       *   - other vec:
       *       const vec4 &v;
       * RETURNS:
       *   (vec4 &) result vector.
       */
      vec4 & operator+=( const vec4 &v )
      {
        X += v.X, Y += v.Y, Z += v.Z, W += v.W;

        return *this;
      } /* End of 'operator+=' function */

      /* Operator '-=' redefenition function.
       * ARGUMENTS:
       *   - other vec:
       *       const vec4 &v;
       * RETURNS:
       *   (vec4 &) result vector.
       */
      vec4 & operator-=( const vec4 &v )
      {
        X -= v.X, Y -= v.Y, Z -= v.Z, W -= v.W;

        return *this;
      } /* End of 'operator-=' function */

      /* Operator '*=' redefenition function.
       * ARGUMENTS:
       *   - other vec:
       *       const vec4 &v;
       * RETURNS:
       *   (vec4 &) result vector.
       */
      vec4 & operator*=( const vec4 &v )
      {
        X *= v.X, Y *= v.Y, Z *= v.Z, W *= v.W;

        return *this;
      } /* End of 'operator*=' function */

      /* Operator '*=' redefenition function.
       * ARGUMENTS:
       *   - number:
       *       const Type &n;
       * RETURNS:
       *   (vec4 &) result vector.
       */
      vec4 & operator*=( const Type &n )
      {
        X *= n, Y *= n, Z *= n, W *= n;

        return *this;
      } /* End of 'operator*=' function */

      /* Operator '/=' redefenition function.
       * ARGUMENTS:
       *   - number:
       *       const Type &n;
       * RETURNS:
       *   (vec4 &) result vector.
       */
      vec4 & operator/=( const Type &n )
      {
        X /= n, Y /= n, Z /= n, W /= n;

        return *this;
      } /* End of 'operator/=' function */

      /* Normalize vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4 &) result vector.
       */
      vec4 & Normalize( VOID )
      {
        Type length = !*this;

        if (length == 0)
          X = Y = Z = W = 0;
        else
          X /= length, Y /= length, Z /= length, W /= length;

        return *this;
      } /* End of 'Normalize' function */

      /* Normalize vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 Normalizing( VOID ) const
      {
        Type length = !*this;

        if (length == 0)
          return Zero();

        return vec4(X / length, Y / length, Z / length, W / length);
      } /* End of 'Normalizing' function */

      /* Get length square of vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) result.
       */
      Type Length2( VOID ) const
      {
        return X * X + Y * Y + Z * Z + W * W;
      } /* End of 'Length2' function */

      /* Get distance to point function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) result.
       */
      Type Distance( const vec4 &P ) const
      {
        return !(*this - P);
      } /* End of 'Distance' function */

      /* Get null vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) result vector.
       */
      static vec4 Zero( VOID )
      {
        return vec4(0);
      } /* End of 'Zero' function */

      /* Get vector with random coords from 0 to 1 function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) result vector.
       */
      static vec4 Rnd0( VOID )
      {
        return vec4(rand() / (Type)RAND_MAX, rand() / (Type)RAND_MAX, rand() / (Type)RAND_MAX, rand() / (Type)RAND_MAX);
      } /* End of 'Rnd0' function */

      /* Get vector with random coords from -1 to 1 function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) result vector.
       */
      static vec4 Rnd1( VOID )
      {
        return vec4(rand() * 2 / (Type)RAND_MAX - 1, rand() * 2 / (Type)RAND_MAX - 1,
                    rand() * 2 / (Type)RAND_MAX - 1, rand() * 2 / (Type)RAND_MAX - 1);
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
        else if (i == 2)
          return Z;
        else
          return W;
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
        else if (i == 2)
          return Z;
        else
          return W;
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

    }; /* End of 'vec4' class */
} /* end of 'mth' namespace */

#endif /* __mth_vec4_h_ */

/* END OF 'mth_vec4.h' FILE */

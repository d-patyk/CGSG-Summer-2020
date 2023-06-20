/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : mth_vec2.h
 * PURPOSE     : Math vec2 definitions.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#ifndef __mth_vec2_h_
#define __mth_vec2_h_

#include "mthdef.h"
#include <cstdlib>
#include <math.h>

/* Space math namespace */
namespace mth
{
  /* 2D vector representation type */
  template<class Type>
    class vec2
    {
    private:
      Type X, Y;
    public:
      template<class OtherType>
        friend class matr;

      /* Constructor function.
       * ARGUMENTS: None.
       */
      vec2( VOID ) : X(0), Y(0)
      {
      } /* End of 'vec2' function */

      /* Constructor function.
       * ARGUMENTS:
       *   - vec coords:
       *       Type X, Y;
       */
      vec2( Type X, Type Y ) : X(X), Y(Y)
      {
      } /* End of 'vec2' function */

      /* Constructor function.
       * ARGUMENTS:
       *   - vec coord:
       *       Type a;
       */
      vec2( Type a ) : X(a), Y(a)
      {
      } /* End of 'vec2' function */

      /* Operator '+' redefenition function.
       * ARGUMENTS:
       *   - other vec:
       *       const vec2 &v;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator+( const vec2 &v ) const
      {
        return vec2(X + v.X, Y + v.Y);
      } /* End of 'operator+' function */

      /* Operator '+' redefenition function.
       * ARGUMENTS:
       *   - other vec:
       *       const vec2 &v;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator-( const vec2 &v ) const
      {
        return vec2(X - v.X, Y - v.Y);
      } /* End of 'operator-' function */

      /* Operator '*' redefenition function.
       * ARGUMENTS:
       *   - other vec:
       *       const vec2 &v;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator*( const vec2 &v ) const
      {
        return vec2(X * v.X, Y * v.Y);
      } /* End of 'operator*' function */

      /* Operator '*' redefenition function.
       * ARGUMENTS:
       *   - number:
       *       const Type num;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator*( const Type &n ) const
      {
        return vec2(X * n, Y * n);
      } /* End of 'operator*' function */

      /* Operator '/' redefenition function.
       * ARGUMENTS:
       *   - number:
       *       const Type num;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator/( const Type &n ) const
      {
        return vec2(X / n, Y / n);
      } /* End of 'operator/' function */

      /* Operator '!' redefenition function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) result.
       */
      Type operator!( VOID ) const
      {
        return sqrt(X * X + Y * Y);
      } /* End of 'operator!' function */

      /* Operator '&' redefenition function.
       * ARGUMENTS:
       *   - other vec:
       *       const vec2 &v;
       * RETURNS:
       *   (Type) result.
       */
      Type operator&( const vec2 &v ) const
      {
        return X * v.X + Y * v.Y;
      } /* End of 'operator&' function */

      /* Operator '+=' redefenition function.
       * ARGUMENTS:
       *   - other vec:
       *       const vec2 &v;
       * RETURNS:
       *   (vec2 &) result vector.
       */
      vec2 & operator+=( const vec2 &v )
      {
        X += v.X, Y += v.Y;

        return *this;
      } /* End of 'operator+=' function */

      /* Operator '-=' redefenition function.
       * ARGUMENTS:
       *   - other vec:
       *       const vec2 &v;
       * RETURNS:
       *   (vec2 &) result vector.
       */
      vec2 & operator-=( const vec2 &v )
      {
        X -= v.X, Y -= v.Y;

        return *this;
      } /* End of 'operator-=' function */

      /* Operator '*=' redefenition function.
       * ARGUMENTS:
       *   - other vec:
       *       const vec2 &v;
       * RETURNS:
       *   (vec2 &) result vector.
       */
      vec2 & operator*=( const vec2 &v )
      {
        X *= v.X, Y *= v.Y;

        return *this;
      } /* End of 'operator*=' function */

      /* Operator '*=' redefenition function.
       * ARGUMENTS:
       *   - number:
       *       const Type &n;
       * RETURNS:
       *   (vec2 &) result vector.
       */
      vec2 & operator*=( const Type &n )
      {
        X *= n, Y *= n;

        return *this;
      } /* End of 'operator*=' function */

      /* Operator '/=' redefenition function.
       * ARGUMENTS:
       *   - number:
       *       const Type &n;
       * RETURNS:
       *   (vec2 &) result vector.
       */
      vec2 & operator/=( const Type &n )
      {
        X /= n, Y /= n;

        return *this;
      } /* End of 'operator/=' function */

      /* Normalize vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2 &) result vector.
       */
      vec2 & Normalize( VOID )
      {
        Type length = !*this;

        if (length == 0)
          X = Y = 0;
        else
          X /= length, Y /= length;

        return *this;
      } /* End of 'Normalize' function */

      /* Normalize vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 Normalizing( VOID ) const
      {
        Type length = !*this;

        if (length == 0)
          return Zero();

        return vec2(X / length, Y / length);
      } /* End of 'Normalizing' function */

      /* Get length square of vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) result.
       */
      Type Length2( VOID ) const
      {
        return X * X + Y * Y;
      } /* End of 'Length2' function */

      /* Get distance to point function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) result.
       */
      Type Distance( const vec2 &P ) const
      {
        return !(*this - P);
      } /* End of 'Distance' function */

      /* Get null vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) result vector.
       */
      static vec2 Zero( VOID )
      {
        return vec2(0);
      } /* End of 'Zero' function */

      /* Get vector with random coords from 0 to 1 function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) result vector.
       */
      static vec2 Rnd0( VOID )
      {
        return vec2(rand() / (Type)RAND_MAX, rand() / (Type)RAND_MAX);
      } /* End of 'Rnd0' function */

      /* Get vector with random coords from -1 to 1 function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) result vector.
       */
      static vec2 Rnd1( VOID )
      {
        return vec2(rand() * 2 / (Type)RAND_MAX - 1, rand() * 2 / (Type)RAND_MAX - 1);
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
        else
          return Y;
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
        else
          return Y;
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

    }; /* End of 'vec2' class */
} /* end of 'mth' namespace */

#endif /* __mth_vec2_h_ */

/* END OF 'mth_vec2.h' FILE */

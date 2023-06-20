/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : mth_matr.h
 * PURPOSE     : Math matr definitions.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#ifndef __mth_matr_h_
#define __mth_matr_h_
#include "mthdef.h"

/* Space math namespace */
namespace mth
{
  /* Matrix representation type */
  template<class Type>
    class matr
    {
    private:
      Type A[4][4];
      mutable Type InvA[4][4];
      mutable bool IsInverseEvaluated;

      /* Evaluate inverse matrix function
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID EvaluateInverseMatrix( VOID ) const
      {
        if (IsInverseEvaluated)
          return;
        IsInverseEvaluated = true;

        DBL det = !*this;

        InvA[0][0] =  Determ3x3(A[1][1], A[1][2], A[1][3],
                                A[2][1], A[2][2], A[2][3],
                                A[3][1], A[3][2], A[3][3]) / det;

        InvA[1][0] = -Determ3x3(A[1][0], A[1][2], A[1][3],
                                A[2][0], A[2][2], A[2][3],
                                A[3][0], A[3][2], A[3][3]) / det;

        InvA[2][0] =  Determ3x3(A[1][0], A[1][1], A[1][3],
                                A[2][0], A[2][1], A[2][3],
                                A[3][0], A[3][1], A[3][3]) / det;

        InvA[3][0] = -Determ3x3(A[1][0], A[1][1], A[1][2],
                                A[2][0], A[2][1], A[2][2],
                                A[3][0], A[3][1], A[3][2]) / det;

        InvA[0][1] = -Determ3x3(A[0][1], A[0][2], A[0][3],
                                A[2][1], A[2][2], A[2][3],
                                A[3][1], A[3][2], A[3][3]) / det;

        InvA[1][1] =  Determ3x3(A[0][0], A[0][2], A[0][3],
                                A[2][0], A[2][2], A[2][3],
                                A[3][0], A[3][2], A[3][3]) / det;

        InvA[2][1] = -Determ3x3(A[0][0], A[0][1], A[0][3],
                                A[2][0], A[2][1], A[2][3],
                                A[3][0], A[3][1], A[3][3]) / det;

        InvA[3][1] =  Determ3x3(A[0][0], A[0][1], A[0][2],
                                A[2][0], A[2][1], A[2][2],
                                A[3][0], A[3][1], A[3][2]) / det;

        InvA[0][2] =  Determ3x3(A[0][1], A[0][2], A[0][3],
                                A[1][1], A[1][2], A[1][3],
                                A[3][1], A[3][2], A[3][3]) / det;

        InvA[1][2] = -Determ3x3(A[0][0], A[0][2], A[0][3],
                                A[1][0], A[1][2], A[1][3],
                                A[3][0], A[3][2], A[3][3]) / det;

        InvA[2][2] =  Determ3x3(A[0][0], A[0][1], A[0][3],
                                A[1][0], A[1][1], A[1][3],
                                A[3][0], A[3][1], A[3][3]) / det;

        InvA[3][2] = -Determ3x3(A[0][0], A[0][1], A[0][2],
                                A[1][0], A[1][1], A[1][2],
                                A[3][0], A[3][1], A[3][2]) / det;

        InvA[0][3] = -Determ3x3(A[0][1], A[0][2], A[0][3],
                                A[1][1], A[1][2], A[1][3],
                                A[2][1], A[2][2], A[2][3]) / det;

        InvA[1][3] =  Determ3x3(A[0][0], A[0][2], A[0][3],
                                A[1][0], A[1][2], A[1][3],
                                A[2][0], A[2][2], A[2][3]) / det;

        InvA[2][3] = -Determ3x3(A[0][0], A[0][1], A[0][3],
                                A[1][0], A[1][1], A[1][3],
                                A[2][0], A[2][1], A[2][3]) / det;

        InvA[3][3] =  Determ3x3(A[0][0], A[0][1], A[0][2],
                                A[1][0], A[1][1], A[1][2],
                                A[2][0], A[2][1], A[2][2]) / det;
      } /* End of 'EvaluateInverseMatrix' function */
    public:
      /* Constructor function.
       * ARGUMENTS: None.
       */
      matr( VOID ) : IsInverseEvaluated(false)
      {
      } /* End of 'matr' function */

      /* Constructor function.
       * ARGUMENTS:
       *   - matrix values:
       *       Type a00, Type a01, Type a02, Type a03,
       *       Type a10, Type a11, Type a12, Type a13,
       *       Type a20, Type a21, Type a22, Type a23,
       *       Type a30, Type a31, Type a32, Type a33;
       */
      matr( Type a00, Type a01, Type a02, Type a03,
            Type a10, Type a11, Type a12, Type a13,
            Type a20, Type a21, Type a22, Type a23,
            Type a30, Type a31, Type a32, Type a33) : IsInverseEvaluated(false)
      {
        A[0][0] = a00;
        A[0][1] = a01;
        A[0][2] = a02;
        A[0][3] = a03;

        A[1][0] = a10;
        A[1][1] = a11;
        A[1][2] = a12;
        A[1][3] = a13;

        A[2][0] = a20;
        A[2][1] = a21;
        A[2][2] = a22;
        A[2][3] = a23;

        A[3][0] = a30;
        A[3][1] = a31;
        A[3][2] = a32;
        A[3][3] = a33;
      } /* End of 'matr' function */

      /* Constructor function.
       * ARGUMENTS:
       *   - matrix values:
       *       Type B[4][4];
       */
      matr( Type B[4][4] ) : IsInverseEvaluated(false)
      {
        A[0][0] = B[0][0];
        A[0][1] = B[0][1];
        A[0][2] = B[0][2];
        A[0][3] = B[0][3];

        A[1][0] = B[1][0];
        A[1][1] = B[1][1];
        A[1][2] = B[1][2];
        A[1][3] = B[1][3];

        A[2][0] = B[2][0];
        A[2][1] = B[2][1];
        A[2][2] = B[2][2];
        A[2][3] = B[2][3];

        A[3][0] = B[3][0];
        A[3][1] = B[3][1];
        A[3][2] = B[3][2];
        A[3][3] = B[3][3];
      } /* End of 'matr' function */

      /* Operator '*' redefenition [matr multiply matr] function.
       * ARGUMENTS:
       *   - matrix:
       *       const matr &M;
       * RETURNS:
       *   (matr) result matrix.
       */
      matr operator*( const matr &M ) const
      {
        return matr(A[0][0] * M.A[0][0] + A[0][1] * M.A[1][0] + A[0][2] * M.A[2][0] + A[0][3] * M.A[3][0],
                    A[0][0] * M.A[0][1] + A[0][1] * M.A[1][1] + A[0][2] * M.A[2][1] + A[0][3] * M.A[3][1],
                    A[0][0] * M.A[0][2] + A[0][1] * M.A[1][2] + A[0][2] * M.A[2][2] + A[0][3] * M.A[3][2],
                    A[0][0] * M.A[0][3] + A[0][1] * M.A[1][3] + A[0][2] * M.A[2][3] + A[0][3] * M.A[3][3],
                    A[1][0] * M.A[0][0] + A[1][1] * M.A[1][0] + A[1][2] * M.A[2][0] + A[1][3] * M.A[3][0],
                    A[1][0] * M.A[0][1] + A[1][1] * M.A[1][1] + A[1][2] * M.A[2][1] + A[1][3] * M.A[3][1],
                    A[1][0] * M.A[0][2] + A[1][1] * M.A[1][2] + A[1][2] * M.A[2][2] + A[1][3] * M.A[3][2],
                    A[1][0] * M.A[0][3] + A[1][1] * M.A[1][3] + A[1][2] * M.A[2][3] + A[1][3] * M.A[3][3],
                    A[2][0] * M.A[0][0] + A[2][1] * M.A[1][0] + A[2][2] * M.A[2][0] + A[2][3] * M.A[3][0],
                    A[2][0] * M.A[0][1] + A[2][1] * M.A[1][1] + A[2][2] * M.A[2][1] + A[2][3] * M.A[3][1],
                    A[2][0] * M.A[0][2] + A[2][1] * M.A[1][2] + A[2][2] * M.A[2][2] + A[2][3] * M.A[3][2],
                    A[2][0] * M.A[0][3] + A[2][1] * M.A[1][3] + A[2][2] * M.A[2][3] + A[2][3] * M.A[3][3],
                    A[3][0] * M.A[0][0] + A[3][1] * M.A[1][0] + A[3][2] * M.A[2][0] + A[3][3] * M.A[3][0],
                    A[3][0] * M.A[0][1] + A[3][1] * M.A[1][1] + A[3][2] * M.A[2][1] + A[3][3] * M.A[3][1],
                    A[3][0] * M.A[0][2] + A[3][1] * M.A[1][2] + A[3][2] * M.A[2][2] + A[3][3] * M.A[3][2],
                    A[3][0] * M.A[0][3] + A[3][1] * M.A[1][3] + A[3][2] * M.A[2][3] + A[3][3] * M.A[3][3]);
      } /* End of 'operator*' function */

    private:
      /* Eval matrix3x3 determinant function.
       * ARGUMENTS:
       *   - matrix values:
       *       Type a00, Type a01, Type a02,
       *       Type a10, Type a11, Type a12,
       *       Type a20, Type a21, Type a22;
       * RETURNS:
       *   (Type) result.
       */
      Type Determ3x3( Type a00, Type a01, Type a02,
                      Type a10, Type a11, Type a12,
                      Type a20, Type a21, Type a22) const
      {
        return a00 * a11 * a22 - a00 * a12 * a21 - a01 * a10 * a22 +
               a01 * a12 * a20 + a02 * a10 * a21 - a02 * a11 * a20;
      } /* End of 'Determ3x3' function */

    public:
      /* Operator '!' redefenition [determinant] function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) result.
       */
      Type operator!( VOID ) const
      {
        return
          A[0][0] * Determ3x3(A[1][1], A[1][2], A[1][3],
                              A[2][1], A[2][2], A[2][3],
                              A[3][1], A[3][2], A[3][3]) -
          A[0][1] * Determ3x3(A[1][0], A[1][2], A[1][3],
                              A[2][0], A[2][2], A[2][3],
                              A[3][0], A[3][2], A[3][3]) +
          A[0][2] * Determ3x3(A[1][0], A[1][1], A[1][3],
                              A[2][0], A[2][1], A[2][3],
                              A[3][0], A[3][1], A[3][3]) -
          A[0][3] * Determ3x3(A[1][0], A[1][1], A[1][2],
                              A[2][0], A[2][1], A[2][2],
                              A[3][0], A[3][1], A[3][2]);
      } /* End of 'operator!' function */

      /* Operator 'Type *' redefenition function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type *) pointer to first value.
       */
      operator Type *( VOID )
      {
        return A[0];
      } /* End of 'operator Type *' function */

      /* Operator 'const Type *' redefenition function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (const Type *) pointer to first value.
       */
      operator const Type *( VOID ) const
      {
        return A[0];
      } /* End of 'operator const Type *' function */

      /* Evaluate inverse matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr) result matrix.
       */
      matr Inverse( VOID ) const
      {
        EvaluateInverseMatrix();
        return matr(InvA);
      } /* End of 'Inverse' function */

      /* Evaluate transpose matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr) result matrix.
       */
      matr Transpose( VOID ) const
      {
        return matr(A[0][0], A[0][1], A[0][2], A[0][3],
                    A[1][0], A[1][1], A[1][2], A[1][3],
                    A[2][0], A[2][1], A[2][2], A[2][3],
                    A[3][0], A[3][1], A[3][2], A[3][3]);
      } /* End of 'Transpose' function */

      /* Get identity matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr) result matrix.
       */
      static matr Identity( VOID )
      {
        return matr(1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1);
      } /* End of 'Identity' function */

      /* Get rotate around X axis matrix function.
       * ARGUMENTS:
       *   - angle:
       *       const DBL &Angle;
       * RETURNS:
       *   (matr) result matrix.
       */
      static matr RotateX( const DBL &Angle )
      {
        DBL An = D2R(Angle);
        Type co = cos(An), si = sin(An);
        
        return matr(1,   0,  0, 0,
                    0,  co, si, 0,
                    0, -si, co, 0,
                    0,   0,  0, 1);
      } /* End of 'RotateX' function */

      /* Get rotate around Y axis matrix function.
       * ARGUMENTS:
       *   - angle:
       *       const DBL &Angle;
       * RETURNS:
       *   (matr) result matrix.
       */
      static matr RotateY( const DBL &Angle )
      {
        DBL An = D2R(Angle);
        Type co = cos(An), si = sin(An);
        
        return matr(co, 0, -si, 0,
                     0, 1,   0, 0,
                    si, 0,  co, 0,
                     0, 0,   0, 1);
      } /* End of 'RotateY' function */

      /* Get rotate around Z axis matrix function.
       * ARGUMENTS:
       *   - angle:
       *       const DBL &Angle;
       * RETURNS:
       *   (matr) result matrix.
       */
      static matr RotateZ( const DBL &Angle )
      {
        DBL An = D2R(Angle);
        Type co = cos(An), si = sin(An);
        return matr( co, si, 0, 0,
                    -si, co, 0, 0,
                      0,  0, 1, 0,
                      0,  0, 0, 1);
      } /* End of 'RotateZ' function */

      /* Get rotate around vector matrix function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<Type> &V;
       *   - angle:
       *       const DBL &Angle;
       * RETURNS:
       *   (matr) result matrix.
       */
      static matr Rotate( const vec3<Type> &V, const DBL &Angle )
      {
        DBL An = D2R(Angle);
        Type c = cos(An), s = sin(An);
        return matr(      c + V.X * V.X * (1 - c),  V.Y * V.X * (1 - c) - V.Z * s, V.Z * V.X * (1 - c) + V.Y * s,
                    V.X * V.Y * (1 - c) + V.Z * s,       c + V.Y * V.Y * (1 - c), V.Z * V.Y * (1 - c) - V.X * s,
                    V.X * V.Z * (1 - c) - V.Y * s, V.Y * V.Z * (1 - c) + V.X * s,       c + V.Z * V.Z * (1 - c));
      } /* End of 'Rotate' function */

      /* Get scale matrix function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<Type> &N;
       * RETURNS:
       *   (matr) result matrix.
       */
      static matr Scale( const vec3<Type> &N )
      {
        return matr(N.X,   0,   0, 0,
                      0, N.Y,   0, 0,
                      0,   0, N.Z, 0,
                      0,   0,   0, 1);
      } /* End of 'Scale' function */

      /* Get translate matrix function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<Type> &N;
       * RETURNS:
       *   (matr) result matrix.
       */
      static matr Translate( const vec3<Type> &N )
      {
        return matr(  1,   0,   0, 0,
                      0,   1,   0, 0,
                      0,   0,   1, 0,
                    N.X, N.Y, N.Z, 1);
      } /* End of 'Translate' function */

      /* Get view matrix function.
       * ARGUMENTS:
       *   - params:
               const vec3<Type> &Loc, &At, &Up1;
       * RETURNS:
       *   (matr) result matrix.
       */
      static matr View( const vec3<Type> &Loc, const vec3<Type> &At, const vec3<Type> &Up1 )
      {
        vec3<Type>
          Dir = (At - Loc).Normalizing(),
          Right = (Dir % Up1).Normalizing(),
          Up = Right % Dir;
        return matr(       Right.X,        Up.X,      -Dir.X, 0,
                           Right.Y,        Up.Y,      -Dir.Y, 0,
                           Right.Z,        Up.Z,      -Dir.Z, 0,
                    -(Loc & Right), -(Loc & Up), (Loc & Dir), 1);
      } /* End of 'View' function */

      /* Get ortho matrix function.
       * ARGUMENTS:
       *   - params:
       *       const DBL Left, const DBL Right,
       *       const DBL Bottom, const DBL Top,
       *       const DBL Near, const DBL Far;
       * RETURNS:
       *   (matr) result matrix.
       */
      static matr Ortho( const DBL Left, const DBL Right,
                         const DBL Bottom, const DBL Top,
                         const DBL Near, const DBL Far )
      {
        return matr(             2 / (Right - Left),                               0,                           0, 0, 
                                                   0,             2 / (Top - Bottom),                           0, 0,
                                                   0,                              0,            2 / (Near - Far), 0,
                    (Right + Left) / (Left - Right), (Top + Bottom) / (Bottom - Top), (Far + Near) / (Near - Far), 1);
      } /* End of 'Ortho' function */

      /* Get frustum matrix function.
       * ARGUMENTS:
       *   - params:
       *       DBL Left, DBL Right,
               DBL Bottom, DBL Top,
               DBL Near, DBL Far;
       * RETURNS:
       *   (matr) result matrix.
       */
      static matr Frustum( const DBL Left, const DBL Right,
                           const DBL Bottom, const DBL Top,
                           const DBL Near, const DBL Far )
      {
        return matr(      2 * Near / (Right - Left),                               0,                             0, 0,
                                                  0,       2 * Near / (Top - Bottom),                             0, 0,
                    (Right + Left) / (Right - Left), (Top + Bottom) / (Top - Bottom),   (Far + Near) / (Near - Far), -1,
                                                  0,                               0, 2 * Near * Far / (Near - Far), 0);
      } /* End of 'Frustum' function */

      /* Transform point function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> TransformPoint( const vec3<Type> &V ) const
      {
        return vec3<Type>(V.X * A[0][0] + V.Y * A[1][0] + V.Z * A[2][0] + A[3][0],
                          V.X * A[0][1] + V.Y * A[1][1] + V.Z * A[2][1] + A[3][1],
                          V.X * A[0][2] + V.Y * A[1][2] + V.Z * A[2][2] + A[3][2]);
      } /* End of 'TransformPoint' function */

      /* Transform vector function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> TransformVector( const vec3<Type> &V ) const
      {
        return vec3<Type>(V.X * A[0][0] + V.Y * A[1][0] + V.Z * A[2][0],
                          V.X * A[0][1] + V.Y * A[1][1] + V.Z * A[2][1],
                          V.X * A[0][2] + V.Y * A[1][2] + V.Z * A[2][2]);
      } /* End of 'TransformVector' function */

      /* Transform normal vector function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> TransformNormal( const vec3<Type> &V ) const
      {
        EvaluateInverseMatrix();
        return vec3<Type>(V.X * InvA[0][0] + V.Y * InvA[0][1] + V.Z * InvA[0][2],
                          V.X * InvA[1][0] + V.Y * InvA[1][1] + V.Z * InvA[1][2],
                          V.X * InvA[2][0] + V.Y * InvA[2][1] + V.Z * InvA[2][2]);
      } /* End of 'TransformNormal' function */

      /* Transform vector function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> Transform4x4( const vec3<Type> &V ) const
      {
        return vec3<Type>((V.X * A[0][0] + V.Y * A[1][0] + V.Z * A[2][0] + A[3][0]) /
                            (V.X * A[0][3] + V.Y * A[1][3] + V.Z * A[2][3] + A[3][3]),
                          (V.X * A[0][1] + V.Y * A[1][1] + V.Z * A[2][1] + A[3][1]) /
                            (V.X * A[0][3] + V.Y * A[1][3] + V.Z * A[2][3] + A[3][3]),
                          (V.X * A[0][2] + V.Y * A[1][2] + V.Z * A[2][2] + A[3][2]) /
                            (V.X * A[0][3] + V.Y * A[1][3] + V.Z * A[2][3] + A[3][3]));
      } /* End of 'Transform4x4' function */
    }; /* End of 'matr' class */
} /* end of 'mth' namespace */

#endif /* __mth_matr_h_ */

/* END OF 'mth_matr.h' FILE */


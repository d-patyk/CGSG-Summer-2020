/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : mth_camera.h
 * PURPOSE     : Math camera definitions.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#ifndef __mth_camera_h_
#define __mth_camera_h_
#include "mthdef.h"

/* Space math namespace */
namespace mth
{
  /* Camera representation type */
  class camera
  {
  public:
    /* Camera parameters */
    FLT ProjSize, ProjDist, ProjFarClip;
    vec3<FLT> Loc, At, Up, Dir, Right;
    matr<FLT> MatrV, MatrP, MatrVP;

    /* Constructor function.
     * ARGUMENTS:
     *   - camera params:
     *       const FLT &ProjSize,  const FLT &ProjDist, const FLT &ProjFarClip,
     *       const vec3<FLT> &Loc, const vec3<FLT> &At, const vec3<FLT> &Up;
     */
    camera( const FLT &ProjSize,  const FLT &ProjDist, const FLT &ProjFarClip,
            const vec3<FLT> &Loc, const vec3<FLT> &At, const vec3<FLT> &Up ) :
      ProjSize(ProjSize), ProjDist(ProjDist), ProjFarClip(ProjFarClip),
      Loc(Loc), At(At), Up(Up)
    {
      SetView(Loc, At, Up);
    } /* End of 'camera' function */

    /* Set camera projection function.
     * ARGUMENTS:
     *   - width & height:
     *       INT W, INT H;
     * RETURNS: None.
     */
    VOID SetProj( INT W, INT H )
    {
      FLT ratio_x, ratio_y;

      ratio_x = ratio_y = ProjSize / 2;
      if (W > H)
        ratio_x *= (FLT)W / H;
      else
        ratio_x *= (FLT)H / W;

      MatrP = matr<FLT>::Frustum(-ratio_x, ratio_x, -ratio_y, ratio_y, ProjDist, ProjFarClip);
      MatrVP = MatrV * MatrP;
    } /* End of 'SetProj' function s*/

    /* Set camera position function.
     * ARGUMENTS:
     *   - location, at-object coords and Up1(you know, what is it):
     *       vec3<FLT> Loc, vec3<FLT> At, vec3<FLT> Up1;
     * RETURNS: None.
     */
    VOID SetView( vec3<FLT> Loc, vec3<FLT> At, vec3<FLT> Up1 )
    {
      this->Loc = Loc, this->At = At;
      Dir = (At - Loc).Normalizing(),
      Right = (Dir % Up1).Normalizing(),
      Up = Right % Dir;
      MatrV = matr<FLT>::View(Loc, At, Up1);
      MatrVP = MatrV * MatrP;
    } /* End of 'SetView' function */
  }; /* End of 'camera' class */
} /* end of 'mth' namespace */

#endif /* __mth_camera_h_ */

/* END OF 'mth_camera.h' FILE */


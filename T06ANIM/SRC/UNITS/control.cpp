/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : control.cpp
 * PURPOSE     : Control unit.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#include "../ANIM/anim.h"

/* Control unit class */
class control_unit : public dpgl::units::unit
{
private:
  /* Coords */
  DBL phi = 0, theta = 90, dist = 1;

public:
  /* Constructor function.
   * ARGUMENTS:
   *   - animation context pointer:
   *       anim *Ani;
   */
  control_unit( dpgl::anim *Ani ) : unit(Ani)
  {

  } /* End of 'control_unit' function */

  /* Destructor function.
   * ARGUMENTS: None.
   */
  ~control_unit( VOID ) override
  {
  } /* End of '~control_unit' function */

  /* Response unit function.
   * ARGUMENTS:
   *   - animation context pointer:
           anim *Ani;
   * RETURNS: None.
   */
  VOID Response( dpgl::anim *Ani ) override
  {
    dpgl::input *inp = Ani;

    if (inp->KeysClick[VK_ESCAPE])
    {
      Ani->Exit();
      return;
    }

    if (inp->KeysClick['F'])
      Ani->FlipFullScreen();

    if (inp->Keys[VK_LBUTTON])
    {
      // CHAR Buf[5000];
      // sprintf(Buf, "%i\n", inp->Dy);
      phi -= inp->Dx / 500.0;

      theta -= inp->Dy / 500.0;

      // OutputDebugString(Buf);
    }
    dist -= inp->Dz / 3000.0;

    phi = (phi > 180) ? (phi - 360) : ((phi < -180) ? (phi + 360) : phi);
    theta = (theta > 180) ? (theta - 180) : ((theta < 0) ? (theta + 180) : theta);
    dist = MAX(0.01, dist);

    Ani->Cam.SetView(dpgl::vec3(dist * sin(phi) * sin(theta), dist * cos(theta), dist * sin(theta) * cos(phi)), Ani->Cam.At, dpgl::vec3(0, 1, 0));
  } /* End of 'Response' function */

  /* Render unit function.
   * ARGUMENTS:
   *   - animation context pointer:
           anim *Ani;
   * RETURNS: None.
   */
  VOID Render( dpgl::anim *Ani ) override
  {
  } /* End of 'Render' function */
}; /* End of 'control_unit' class */

/* Unit registration */
static dpgl::anim::unit_register<control_unit> _("Control");

/* END OF 'control.cpp' FILE */

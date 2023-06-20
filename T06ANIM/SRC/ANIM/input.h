/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : input.h
 * PURPOSE     : Input module header.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#ifndef __input_h_
#define __input_h_
#include "../WIN/win.h"
#include <cstdlib>

/* Project namespace */
namespace dpgl
{
  /* Mouse class*/
  class mouse
  {
  private:
    INT &Wheel; /* Wheel link */
    HWND hWnd;  /* Handle window */
  public:
    INT X, Y, Z;    /* Mouse & wheel position */
    INT Dx, Dy, Dz; /* Mouse & wheel delta position */

    /* Constructor function.
     * ARGUMENTS:
     *   - wheel link:
     *       INT &WheelRef;
     *   - handle window:
     *       HWND hWnd;
     */
    mouse( INT &WheelRef, HWND hWnd ) : Wheel(WheelRef), hWnd(hWnd), X(0), Y(0), Z(0), Dx(0), Dy(0), Dz(0)
    {
    } /* End of 'mouse' function */

    /* Response function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Response( VOID )
    {
      static BYTE Keys[256];
      POINT pt;

      GetCursorPos(&pt);
      ScreenToClient(hWnd, &pt);

      Dx = pt.x - X;
      Dy = pt.y - Y;
      X = pt.x;
      Y = pt.y;

      Dz = Wheel;
      Z += Wheel;
      Wheel = 0;

      /*
      GetKeyboardState(Keys);
      for (auto &i : Keys)
        i >>= 7;
      for (int i = 0; i < 256; ++i)
        KeysClick[i] = Keys[i] && !KeysOld[i];
      memcpy(KeysOld, Keys, 256);
      */
    } /* End of 'Response' function */
  }; /* End of 'mouse' class */

  /* Keyboard class */
  class keyboard
  {
  public:
    BYTE Keys[256];      /* Keys' current state */
    BYTE KeysOld[256];   /* Keys' previous state */
    BYTE KeysClick[256]; /* Single keys' clicks */

    /* Constructor function.
     * ARGUMENTS: None.
     */
    keyboard( VOID ) : Keys(), KeysOld(), KeysClick()
    {
      GetKeyboardState(Keys);
      memcpy(KeysOld, Keys, 256);
    } /* End of 'keyboard' function */

    /* Response function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Response( VOID )
    {
      GetKeyboardState(Keys);
      for (auto &i : Keys)
        i >>= 7;
      for (int i = 0; i < 256; ++i)
        KeysClick[i] = Keys[i] && !KeysOld[i];
      memcpy(KeysOld, Keys, 256);
    } /* End of 'Response' function */
  }; /* End of 'keyboard' class */

  /* Joystick class */
  class joystick
  {
  public:
    /* Constructor function.
     * ARGUMENTS: None.
     */
    joystick( VOID )
    {
    } /* End of 'joystick' function */

    /* Response function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Response( VOID )
    {
    } /* End of 'Response' function */
  }; /* End of 'joystick' class */

  class input : public mouse, public keyboard, public joystick
  {
  public:
    /* Constructor function
     * ARGUMENTS:
     *   - wheel link:
     *       INT &WheelRef;
     *   - handle window:
     *       HWND hWnd;
     */
    input( INT &WheelRef, HWND hWnd) : mouse(WheelRef, hWnd), keyboard(), joystick()
    {
    } /* End of 'input' function */

    /* Response function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Response( VOID )
    {
      mouse::Response();
      keyboard::Response();
      joystick::Response();
    } /* End of 'Response' function */
  };
} /* end of 'dpgl' namespace */

#endif /* __input_h_ */

/* END OF 'input.h' FILE */

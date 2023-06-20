/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : main.cpp
 * PURPOSE     : Main file.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#include "../ANIM/anim.h"

#if 0
bool Func( void )
{
  unf F("BIN/G3DM/ficus.g3dm");

  if (!F)
    return false;

  DWORD Sign;
  F.Read(&Sign);

  DWORD PMT[3];
  F.Read(PMT, 3);

  DWORD Nums[3];
  F.Read(Nums, 3);
  std::vector<dpgl::vertex::std> V;
  V.resize(Nums[0]);
  F.Read(&V[0], Nums[0]);
  std::vector<int> I;
  I.resize(Nums[1]);
  F.Read(&I[0], Nums[1]);
  return true;
}
#endif /* 0 */

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       _In_ HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       _In_opt_ HINSTANCE hPrevInstance;
 *   - command line string:
 *       _In_ CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       _In_ INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */

INT WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
                    _In_ CHAR *CmdLine, _In_ INT ShowCmd )
{
  dpgl::anim *Ani = dpgl::anim::GetPtr();
  dpgl::units::scene MyScene(Ani);

  MyScene << "Control" << "Test";
  // Func();

  // return 30;

  // Ani.win::FlipFullScreen();
  return Ani->SceneSet(&MyScene).Run();
} /* End of 'WinMain' function */

/* END OF 'main.cpp' FILE */

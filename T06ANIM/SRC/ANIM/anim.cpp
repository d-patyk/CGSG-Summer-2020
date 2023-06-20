/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : anim.cpp
 * PURPOSE     : Animation module main file.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#include "anim.h"
#include <cstdio>

/* Project namespace */
namespace dpgl
{
  /***
   * Unit functions' definitions
   ***/

  /* Constructor function.
   * ARGUMENTS:
   *   - animation context pointer:
   *       anim *Ani;
   */
  units::unit::unit( anim *Ani )
  {
  } /* End of 'units::unit::unit' function */

  /* Destructor function.
   * ARGUMENTS: None.
   */
  units::unit::~unit( VOID )
  {
  } /* End of 'units::unit::~unit' function */

  /* Response unit function.
   * ARGUMENTS:
   *   - animation context pointer:
           anim *Ani;
   * RETURNS: None.
   */
  VOID units::unit::Response( anim *Ani )
  {
  } /* End of 'units::unit::Response' function */

  /* Render unit function.
   * ARGUMENTS:
   *   - animation context pointer:
           anim *Ani;
   * RETURNS: None.
   */
  VOID units::unit::Render( anim *Ani )
  {
  } /* End of 'units::unit::Render' function */


  /***
   * Scene functions' definitions
   ***/

  /* Constructor function.
   * ARGUMENTS:
   *   - animation context pointer:
   *       anim *Ani;
   */
  units::scene::scene( anim *Ani ) : unit::unit(Ani)
  {
  } /* End of 'units::scene::scene' function */

  /* Destructor function.
   * ARGUMENTS: None.
   */
  units::scene::~scene( VOID )
  {
    Units.Walk([]( unit *Uni ){ delete Uni; });
  } /* End of 'units::scene::~scene' function */

  /* Response scene function.
   * ARGUMENTS:
   *   - animation context pointer:
           anim *Ani;
   * RETURNS: None.
   */
  VOID units::scene::Response( anim *Ani )
  {
    Units.Walk([Ani]( unit *Uni ){ Uni->Response(Ani); });
  } /* End of 'units::scene::Response' function */

  /* Render scene function.
   * ARGUMENTS:
   *   - animation context pointer:
           anim *Ani;
   * RETURNS: None.
   */
  VOID units::scene::Render( anim *Ani )
  {
    Units.Walk([Ani]( unit *Uni ){ Uni->Render(Ani); });
  } /* End of 'units::scene::Render' function */

#if 0
  /* Operator '<<' redefenition function.
   * ARGUMENTS:
   *   - new 'unit' element pointer:
   *       unit *Uni;
   * RETURNS:
   *   (scene &) scene link.
   */
  units::scene & units::scene::operator<<( unit *Uni )
  {
    Units << Uni;
    return *this;
  } /* End of 'units::scene::operator<<' function */
#endif

  /* Operator '<<' redefenition function.
   * ARGUMENTS:
   *   - new 'unit' name:
   *       unit *Uni;
   * RETURNS:
   *   (scene &) scene link.
   */
  units::scene & units::scene::operator<<( const std::string &Name )
  {
    anim &Ani = anim::Get();

    if (Ani.UnitNames.find(Name) != Ani.UnitNames.end())
    {
      unit *uni = Ani.UnitNames[Name]();

      Units << uni;
      return *this;
    }
    return *this;
  } /* End of 'units::scene::operator<<' function */


  /***
   * Animation functions' and fields' definitions
   ***/

  anim anim::Anim; /* single tone object of class 'anim' */

  /* Constructor function.
   * ARGUMENTS: None.
   */
  anim::anim( VOID ) : win(), input(win::MouseWheel, win::hWnd), render(win::hWnd, win::Width, win::Height), Scene(nullptr)
  {
  } /* End of 'anim::anim' function */

  /* Get single tone object of class 'anim'
   * ARGUMENTS: None.
   * RETURNS:
   *   (anim &) anim object.
   */
  anim & anim::Get( VOID )
  {
    return Anim;
  } /* End of 'anim::Get' function */

  /* Get single tone object pointer of class 'anim'.
   * ARGUMENTS: None.
   * RETURNS:
   *   (anim *) anim object pointer.
   */
  anim * anim::GetPtr( VOID )
  {
    return &Anim;
  } /* End of 'anim::GetPtr' function */

  /* Render frame function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID anim::Render( VOID )
  {/*
    HDC hDC = GetDC(win::hWnd);*/
    //Ellipse(hDC, 0, 0, 100, 100);
    timer::Response();
    input::Response();
    static DBL lastUpdate = -1000;
    static CHAR Buf[5000];

    if (timer::GlobalTime - lastUpdate > 0.5)
    {
      sprintf_s(Buf, 1000, "%f", timer::FPS);
      SetWindowText(win::hWnd, Buf);
      lastUpdate = timer::GlobalTime;
    }
    render::FrameStart();

    // Тут рисование
    Scene->Response(this);
    Scene->Render(this);

    render::FrameEnd();
    render::FrameCopy();
  } /* End of 'anim::Render' function */


  /* Init function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID anim::Init( VOID )
  {
  } /* End of 'anim::Init' function */

  /* Close function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID anim::Close( VOID )
  {
  } /* End of 'anim::Close' function */

  /* Resize function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID anim::Resize( VOID )
  {
    render::Resize(win::Width, win::Height);
    Render();
  } /* End of 'anim::Resize' function */

  /* Timer function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID anim::Timer( VOID )
  {
    Render();
  } /* End of 'anim::Timer' function */

  /* Activate function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID anim::Activate( VOID )
  {
  } /* End of 'anim::Activate' function */

  /* Idle function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID anim::Idle( VOID )
  {
    Render();
  } /* End of 'anim::Idle' function */

  /* Erase function.
   * ARGUMENTS:
   *   - handle draw context
   *       HDC hDC;
   * RETURNS: None.
   */
  VOID anim::Erase( HDC hDC )
  {
  } /* End of 'anim::Erase' function */

  /* Paint function.
   * ARGUMENTS:
   *   - handle draw context
   *       HDC hDC;
   * RETURNS: None.
   */
  VOID anim::Paint( HDC hDC )
  {
    Render();
  } /* End of 'anim::Paint' function */

  /* Set new animation scene function.
   * ARGUMENTS:
   *   - new scene pointer:
   *       units::unit *NewScene;
   * RETURNS:
   *   (anim &) anim link.
   */
  anim & anim::SceneSet( units::unit *NewScene )
  {
    Scene = NewScene;
    return *this;
  } /* End of 'anim::SceneSet' function */
 
#if 0
  /* Operator '<<' redefenition function.
   * ARGUMENTS:
   *   - new 'unit' element pointer:
   *       units::unit *Uni;
   * RETURNS:
   *   (anim &) anim link.
   */
  anim & anim::operator<<( units::unit *Uni )
  {
    units::scene *sc = dynamic_cast<units::scene *>(Scene);
    *sc << Uni;
    return *this;
  } /* End of 'anim::operator<<' function */
#endif

  /* Operator '<<' redefenition function.
   * ARGUMENTS:
   *   - new 'unit' name:
   *       unit *Uni;
   * RETURNS:
   *   (anim &) scene link.
   */
  anim & anim::operator<<( const std::string &Name )
  {
    units::scene *sc = dynamic_cast<units::scene *>(Scene);
    *sc << Name;
    return *this;
  } /* End of 'anim::operator<<' function */

  /* Exit from program function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID anim::Exit( VOID )
  {
    if (IsExit)
      return;
    PostMessage(win::hWnd, WM_CLOSE, NULL, NULL);
    IsExit = 1;
  } /* End of 'anim::Exit' function */

} /* end of 'dpgl' namespace */

/* END OF 'anim.cpp' FILE */

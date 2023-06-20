/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : render.h
 * PURPOSE     : Render module header.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#ifndef __render_h_
#define __render_h_
#include "RES/res.h"

/* Project namespace */
namespace dpgl
{
  /* Render class */
  class render : public primitive_manager, public shader_manager
  {
    HWND &hWnd;           /* Handle window */
    INT &FrameW, &FrameH; /* Frame size */
    HDC hDC;              /* Handle draw context */
    HGLRC hGLRC;          /* Handle GL render context :3 */

  public:
    /* Coordinate system type & current coordinate system type */
    enum struct cs
    {
      WORLD, SCREEN
    } CurrentCS;

    /* Fill type & current fill type */
    enum struct fill
    {
      WIREFRAME, SOLID
    } CurrentFill;
  private:
    stock<cs> CSStack;     /* CS stack */
    stock<fill> FillStack; /* Fill stack*/
  public:
    mth::camera Cam; /* Camera */

    /* Constructor function.
     * ARGUMENTS:
     *   - handle window
     *       HWND &hWnd;
     *   - window size
     *       INT &W, INT &H;
     */
    render( HWND &hWnd, INT &W, INT &H );

    /* Destructor function.
     * ARGUMENTS: None.
     */
    ~render( VOID );

    /* Resize function.
     * ARGUMENTS:
     *   - new size:
     *       INT NewW, INT NewH;
     * RETURNS: None.
     */
    VOID Resize( INT NewW, INT NewH );

    /* Start frame draw function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FrameStart( VOID );

    /* End frame draw function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FrameEnd( VOID );

    /* Copy frame function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FrameCopy( VOID );

    /* Set new 'cs' function.
     * ARGUMENTS:
     *   - new coordinate system type:
     *       cs NewCS;
     * RETURNS: None.
     */
    VOID Set( cs NewCS );

    /* Set new 'fill' function.
     * ARGUMENTS:
     *   - new fill type:
     *       fill NewFill;
     * RETURNS: None.
     */
    VOID Set( fill NewFill );

    /* Push new 'cs' to queue function.
     * ARGUMENTS:
     *   - new coordinate system type:
     *       cs NewCS;
     * RETURNS: None.
     */
    VOID Push( cs NewCS );

    /* Pop last 'cs' from queue function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID PopCS( VOID );

    /* Push new 'fill' to queue function.
     * ARGUMENTS:
     *   - new fill type:
     *       fill NewFill;
     * RETURNS: None.
     */
    VOID Push( fill NewFill );

    /* Pop last 'fill' from queue function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID PopFill( VOID );

    /* Draw primitive.
     * ARGUMENTS:
     *   - primitive:
     *       prim *Pr;
     *   - world matrix:
     *       matr World;
     * RETURNS: None.
     */
    VOID Draw( prim *Pr, matr World );

    /* Draw primitives.
     * ARGUMENTS:
     *   - primitives:
     *       prims &Prs;
     *   - world matrix:
     *       matr World;
     * RETURNS: None.
     */
    VOID Draw( prims &Prs, matr World );
  };
} /* end of 'dpgl' namespace */

#endif /* __render_h_ */

/* END OF 'render.h' FILE */

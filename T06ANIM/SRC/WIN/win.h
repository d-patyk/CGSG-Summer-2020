/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : win.h
 * PURPOSE     : Windows module header.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#ifndef __win_h_
#define __win_h_
#include "../def.h"

/* Project namespace */
namespace dpgl
{
  /* Window class */
  class win
  {
  protected:
    HWND hWnd;           /* window handle */
    INT Width, Height;            /* window size */
    HINSTANCE hInstance; /* application handle */

  protected:
    BOOL IsFullScreen;       /* is full screen enable */
    RECT FullScreenSaveRect; /* full screen save rect..... idk, what it is */
    INT MouseWheel;          /* mouse wheel position */
    BOOL IsInit;             /* is system init */

  private:
    /* Windows message handle function.
     * ARGUMENTS:
     *   - handle window:
     *       HWND hWnd;
     *   - message identifier:
     *       UINT Msg;
     *   - message parameters:
     *       WPARAM wParam, LPARAM lParam.
     * RETURNS:
     *   (LRESULT CALLBACK) handling result.
     */
    static LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg,
                                     WPARAM wParam, LPARAM lParam );

    /* Window class name */
    const CHAR *WND_CLASS_NAME = "My WindowClass";

  public:
    BOOL IsActive; /* Is window active? You can find the answer here */

    /* Constructor function.
     * AGRUMENTS:
     *   - handle of application instance:
     *       HINSTANCE hInstance;
     */
    win( HINSTANCE hInst = GetModuleHandle(NULL) );

    /* Destructor function. 
     * ARGUMENTS: None.
     */
    ~win( VOID );

    /* Run window and message handling function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (INT) program result code.
     */
    INT Run( VOID );

    /* Toggle full screen function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FlipFullScreen( VOID );

  private:
    /***
     * Message cracks
     ***/

    /* WM_CREATE window message handle function.
     * ARGUMENTS:
     *   - structure with creation data:
     *       CREATESTRUCT *CS;
     * RETURNS:
     *   (BOOL) TRUE to continue creation window, FALSE to terminate.
     */
    BOOL OnCreate( CREATESTRUCT *CS );

    /* WM_SIZE window message handle function.
     * ARGUMENTS:
     *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
     *       UINT State;
     *   - new width and height of client area:
     *       INT W, H;
     * RETURNS: None.
     */
    VOID OnSize( UINT State, INT W, INT H );

    /* WM_TIMER window message handle function.
     * ARGUMENTS:
     *   - specified the timer identifier.
     *       INT Id;
     * RETURNS: None.
     */
    VOID OnTimer( INT Id );

    /* WM_MOUSEWHEEL window message handle function.
     * ARGUMENTS:
     *   - mouse window position:
     *       INT X, Y;
     *   - mouse wheel relative delta value:
     *       INT Z;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    VOID OnMouseWheel( INT X, INT Y, INT Z, UINT Keys );

    /* WM_xBUTTONDOWN window message handle function.
     * ARGUMENTS:
     *   - is click double:
     *       BOOL IsDblClick;
     *   - mouse window position:
     *       INT X, Y;
     *   - mouse wheel relative delta value:
     *       INT Z;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    VOID OnButtonDown( BOOL IsDblClick, INT X, INT Y, UINT Keys );

    /* WM_xBUTTONUP window message handle function.
     * ARGUMENTS:
     *   - is click double:
     *       BOOL IsDblClick;
     *   - mouse window position:
     *       INT X, Y;
     *   - mouse wheel relative delta value:
     *       INT Z;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    VOID OnButtonUp( INT X, INT Y, UINT Keys );

    /* WM_ERASEBKGND window message handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS:
     *   (BOOL) TRUE if background is erased, FALSE otherwise.
     */
    BOOL OnEraseBkgnd( HDC hDC );

    /* WM_PAINT window message handle function.
     * ARGUMENTS:
     *   - window device context:
     *       HDC hDC;
     *   - paint message structure pointer:
     *       PAINTSTRUCT *PS;
     * RETURNS: None.
     */
    VOID OnPaint( HDC hDC, PAINTSTRUCT *PS );

    /* WM_CLOSE window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID OnClose( VOID );

    /* WM_DESTROY window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID OnDestroy( VOID );

    /* WM_ACTIVATE window message handle function.
     * ARGUMENTS:
     *   - reason (WA_CLICKACTIVE, WA_ACTIVE or WA_INACTIVE):
     *       UINT Reason;
     *   - handle of active window:
     *       HWND hWndActDeact;
     *   - minimized flag:
     *       BOOL IsMinimized;
     * RETURNS: None.
     */
    VOID OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized );


    /* Init function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Init( VOID )
    {
    } /* End of 'Init' function */

    /* Close function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Close( VOID )
    {
    } /* End of 'Close' function */

    /* Resize function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Resize( VOID )
    {
    } /* End of 'Resize' function */

    /* Timer function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Timer( VOID )
    {
    } /* End of 'Timer' function */

    /* Activate function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Activate( VOID )
    {
    } /* End of 'Activate' function */

    /* Idle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Idle( VOID )
    {
    } /* End of 'Idle' function */

    /* Erase function.
     * ARGUMENTS:
     *   - handle draw context
     *       HDC hDC;
     * RETURNS: None.
     */
    virtual VOID Erase( HDC hDC )
    {
    } /* End of 'Erase' function */

    /* Paint function.
     * ARGUMENTS:
     *   - handle draw context
     *       HDC hDC;
     * RETURNS: None.
     */
    virtual VOID Paint( HDC hDC )
    {
    } /* End of 'Paint' function */
  }; /* End of 'win' class */
} /* end of 'dpgl' namespace */
#endif /* __win_h_ */

/* END OF 'win.h' FILE */

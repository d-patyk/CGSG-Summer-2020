/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : winmsg.cpp
 * PURPOSE     : Windows messages handle.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#include "win.h"

/* Project namespace */
namespace dpgl
{
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
  LRESULT CALLBACK win::WinFunc( HWND hWnd, UINT Msg,
                                 WPARAM wParam, LPARAM lParam )
  {
    win *Win;
    HDC hDC;
    PAINTSTRUCT ps;

    switch (Msg)
    {
    case WM_GETMINMAXINFO:
      ((MINMAXINFO *)lParam)->ptMaxTrackSize.y =
        GetSystemMetrics(SM_CYMAXTRACK) +
        GetSystemMetrics(SM_CYCAPTION) +
        GetSystemMetrics(SM_CYMENU) +
        GetSystemMetrics(SM_CYBORDER) * 2;
      return 0;
    case WM_CREATE:
      /* Attach 'this' pointer to window class to window */
      SetWindowLong(hWnd, 0, (DWORD)((CREATESTRUCT *)lParam)->lpCreateParams);
    default:
      Win = reinterpret_cast<win *>(GetWindowLong(hWnd, 0));
      if (Win != NULL)
        switch (Msg)
        {
        case WM_CREATE:
          Win->IsInit = TRUE;
          Win->hWnd = hWnd;
          return Win->OnCreate((CREATESTRUCT *)lParam) ? 0 : -1;
        case WM_SIZE:
          Win->OnSize(wParam, LOWORD(lParam), HIWORD(lParam));
          return 0;
        case WM_ERASEBKGND:
          return (LRESULT)Win->OnEraseBkgnd((HDC)wParam);
        case WM_PAINT:
          hDC = BeginPaint(hWnd, &ps);
          Win->OnPaint(hDC, &ps);
          EndPaint(hWnd, &ps);
          return 0;
        case WM_TIMER:
          Win->OnTimer((UINT)wParam);
          return 0;
        case WM_ACTIVATE:
          Win->OnActivate((UINT)LOWORD(wParam), (HWND)lParam, (BOOL)HIWORD(wParam));
          return 0;
        case WM_MOUSEWHEEL:
          Win->OnMouseWheel((INT)(SHORT)LOWORD(lParam),
                            (INT)(SHORT)HIWORD(lParam),
                            (INT)(SHORT)HIWORD(wParam),
                            (UINT)(SHORT)LOWORD(wParam));
          return 0;
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
          Win->OnButtonDown(FALSE,
                             (INT)(SHORT)LOWORD(lParam),
                             (INT)(SHORT)HIWORD(lParam),
                             (UINT)(SHORT)LOWORD(wParam));
          return 0;
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
          Win->OnButtonUp((INT)(SHORT)LOWORD(lParam),
                             (INT)(SHORT)HIWORD(lParam),
                             (UINT)(SHORT)LOWORD(wParam));
          return 0;
        case WM_DESTROY:
          Win->OnDestroy();
          PostQuitMessage(30);
          return 0;
        }
    }
    return DefWindowProc(hWnd, Msg, wParam, lParam);
  } /* End of 'win::WinFunc' function */

  /* WM_CREATE window message handle function.
   * ARGUMENTS:
   *   - structure with creation data:
   *       CREATESTRUCT *CS;
   * RETURNS:
   *   (BOOL) TRUE to continue creation window, FALSE to terminate.
   */
  BOOL win::OnCreate( CREATESTRUCT *CS )
  {
    SetTimer(hWnd, 30, 1, NULL); // Init timer
    return TRUE;
  } /* End of 'win::OnCreate' function */

  /* WM_DESTROY window message handle function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID win::OnDestroy( VOID )
  {
    if (IsInit)
      Close(), KillTimer(hWnd, 30); // Killing refresh timer
    else
      KillTimer(hWnd, 30); // Killing init timer
  } /* End of 'win::OnDestroy' function */

  /* WM_SIZE window message handle function.
   * ARGUMENTS:
   *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
   *       UINT State;
   *   - new width and height of client area:
   *       INT W, H;
   * RETURNS: None.
   */
  VOID win::OnSize( UINT State, INT W, INT H )
  {
    this->Width = W;
    this->Height = H;
    if (IsInit)
      Resize();
  } /* End of 'win::OnSize' function */

  /* WM_ERASEBKGND window message handle function.
   * ARGUMENTS:
   *   - device context of client area:
   *       HDC hDC;
   * RETURNS:
   *   (BOOL) TRUE if background is erased, FALSE otherwise.
   */
  BOOL win::OnEraseBkgnd( HDC hDC )
  {
    if (IsInit)
      Erase(hDC);

    return TRUE;
  } /* End of 'win::OnEraseBkgnd' function */

  /* WM_PAINT window message handle function.
   * ARGUMENTS:
   *   - window device context:
   *       HDC hDC;
   *   - paint message structure pointer:
   *       PAINTSTRUCT *PS;
   * RETURNS: None.
   */
  VOID win::OnPaint( HDC hDC, PAINTSTRUCT *PS )
  {
    if (IsInit)
      Paint(hDC);
  } /* End of 'win::OnPaint' function */

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
  VOID win::OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized )
  {
    IsActive = Reason == WA_CLICKACTIVE || Reason == WA_ACTIVE;
    if (IsInit)
      Activate();
  } /* End of 'win::OnActivate' function */

  /* WM_TIMER window message handle function.
   * ARGUMENTS:
   *   - specified the timer identifier.
   *       INT Id;
   * RETURNS: None.
   */
  VOID win::OnTimer( INT Id )
  {
    if (!IsInit)
    {
      KillTimer(hWnd, 30); // Init timer
      SetTimer(hWnd, 30, 1, NULL); // Refresh timer
      IsInit = TRUE;

      // call callbacks
      Init();
      Resize();
      Activate();
      Timer();
      Idle();
    }
    else
      Timer();
  } /* End of 'win::OnTimer' function */

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
  VOID win::OnMouseWheel( INT X, INT Y, INT Z, UINT Keys )
  {
    MouseWheel += Z;
  } /* End of 'win::OnMouseWheel' function */

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
  VOID win::OnButtonDown( BOOL IsDblClick, INT X, INT Y, UINT Keys )
  {
  } /* End of 'win::OnButtonDown' function */

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
  VOID win::OnButtonUp( INT X, INT Y, UINT Keys )
  {
  } /* End of 'win::OnButtonUp' function */

  /* WM_CLOSE window message handle function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID win::OnClose( VOID )
  {
  } /* End of 'win::OnClose' function */
} /* end of 'dpgl' namespace */

/* END OF 'winmsg.cpp' FILE */

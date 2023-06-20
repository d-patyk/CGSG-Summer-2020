/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : win.cpp
 * PURPOSE     : Windows main file.
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
  /* Constructor function.
   * AGRUMENTS:
   *   - handle of application instance:
   *       HINSTANCE hInstance;
   */
  win::win( HINSTANCE hInst ) :
    hInstance(hInst), IsInit(FALSE),
    Width(0), Height(0), FullScreenSaveRect(),
    IsActive(FALSE), IsFullScreen(FALSE),
    MouseWheel(0), hWnd()
  {
    WNDCLASS wc;

    wc.style = CS_VREDRAW | CS_HREDRAW;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(win *);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_ERROR);
    wc.lpszMenuName = NULL;
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WinFunc;
    wc.lpszClassName = WND_CLASS_NAME;

    if (!RegisterClass(&wc))
      MessageBox(NULL, "Error register window class", "ERROR", MB_OK);

    hWnd = CreateWindow(WND_CLASS_NAME, "3D animation",
      WS_OVERLAPPEDWINDOW | WS_VISIBLE,
      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
      NULL, NULL, hInstance, reinterpret_cast<VOID *>(this));

    /*
    ShowWindow(hWnd, SW_SHOWNORMAL);
    UpdateWindow(hWnd);
    */
  } /* End of 'win::win' function */

  /* Destructor function. 
   * ARGUMENTS: None.
   */
  win::~win( VOID )
  {
  } /* End of 'win::~win' function */

  /* Run window and message handling function.
   * ARGUMENTS: None.
   * RETURNS:
   *   (INT) program result code.
   */
  INT win::Run( VOID )
  {
    MSG msg;
    while (TRUE)
      /* Check message at window message queue */
      if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        if (msg.message == WM_QUIT)
          break;
        else
        {
          /* Displatch message to window */
          TranslateMessage(&msg);
          DispatchMessage(&msg);
        }
      else
      {
        if (IsInit)
          Idle();
        /* Idle... */
      }
    return msg.wParam;
  } /* End of 'win::Run' function */

  /* Toggle full screen function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID win::FlipFullScreen( VOID )
  {
    if (!IsFullScreen)
    {
      RECT rc;
      HMONITOR hmon;
      MONITORINFOEX moninfo;

      GetWindowRect(hWnd, &FullScreenSaveRect);

      hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

      moninfo.cbSize = sizeof(moninfo);
      GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

      rc = moninfo.rcMonitor;

      AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);

      SetWindowPos(hWnd, HWND_TOP,
        rc.left, rc.top,
        rc.right - rc.left, rc.bottom - rc.top,
        SWP_NOOWNERZORDER);
      IsFullScreen = TRUE;
    }
    else
    {
      SetWindowPos(hWnd, HWND_TOP,
        FullScreenSaveRect.left, FullScreenSaveRect.top,
        FullScreenSaveRect.right - FullScreenSaveRect.left,
        FullScreenSaveRect.bottom - FullScreenSaveRect.top,
        SWP_NOOWNERZORDER);
      IsFullScreen = FALSE;
    }
  } /* End of 'win::FlipFullScreen' function*/
} /* end of 'dpgl' namespace */

/* END OF 'win.cpp' FILE */

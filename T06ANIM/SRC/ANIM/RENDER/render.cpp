/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : render.cpp
 * PURPOSE     : Render cpp file.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#include <cstdio>
#include "render.h"

/* Debug output function.
 * ARGUMENTS:
 *   - source APi or device:
 *      UINT Source;
 *   - error type:
 *      UINT Type;
 *   - error message id:
 *      UINT Id, 
 *   - message severity:
 *      UINT severity, 
 *   - message text length:
 *      INT Length, 
 *   - message text:
 *      CHAR *Message, 
 *   - user addon parameters pointer:
 *      VOID *UserParam;
 * RETURNS: None.
 */
static VOID APIENTRY glDebugOutput( UINT Source, UINT Type, UINT Id, UINT Severity,
                                    INT Length, const CHAR *Message, const VOID *UserParam )
{
  INT len = 0;
  static CHAR Buf[10000];

  /* Ignore non-significant error/warning codes */
  if (Id == 131169 || Id == 131185 || Id == 131218 || Id == 131204)
    return;

  len += sprintf_s(Buf + len, 100, "Debug message (%i) %s\n", Id, Message);

  switch (Source)
  {
  case GL_DEBUG_SOURCE_API:
    len += sprintf_s(Buf + len, 1000, "Source: API\n");
    break;
  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
    len += sprintf_s(Buf + len, 1000, "Source: Window System\n");
    break;
  case GL_DEBUG_SOURCE_SHADER_COMPILER:
    len += sprintf_s(Buf + len, 1000, "Source: Shader Compiler\n");
    break;
  case GL_DEBUG_SOURCE_THIRD_PARTY:
    len += sprintf_s(Buf + len, 1000, "Source: Third Party\n");
    break;
  case GL_DEBUG_SOURCE_APPLICATION:
    len += sprintf_s(Buf + len, 1000, "Source: Application");
    break;
  case GL_DEBUG_SOURCE_OTHER:
    len += sprintf_s(Buf + len, 1000, "Source: Other");
    break;
  }
  len += sprintf_s(Buf + len, 1000, "\n");

  switch (Type)
  {
  case GL_DEBUG_TYPE_ERROR:
    len += sprintf_s(Buf + len, 1000, "Type: Error");
    break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
    len += sprintf_s(Buf + len, 1000, "Type: Deprecated Behaviour");
    break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
    len += sprintf_s(Buf + len, 1000, "Type: Undefined Behaviour");
    break; 
  case GL_DEBUG_TYPE_PORTABILITY:
    len += sprintf_s(Buf + len, 1000, "Type: Portability");
    break;
  case GL_DEBUG_TYPE_PERFORMANCE:
    len += sprintf_s(Buf + len, 1000, "Type: Performance");
    break;
  case GL_DEBUG_TYPE_MARKER:
    len += sprintf_s(Buf + len, 1000, "Type: Marker");
    break;
  case GL_DEBUG_TYPE_PUSH_GROUP:
    len += sprintf_s(Buf + len, 1000, "Type: Push Group");
    break;
  case GL_DEBUG_TYPE_POP_GROUP:
    len += sprintf_s(Buf + len, 1000, "Type: Pop Group");
    break;
  case GL_DEBUG_TYPE_OTHER:
    len += sprintf_s(Buf + len, 1000, "Type: Other");
    break;
  }
  len += sprintf_s(Buf + len, 1000, "\n");

  switch (Severity)
  {
  case GL_DEBUG_SEVERITY_HIGH:
    len += sprintf_s(Buf + len, 1000, "Severity: high");
    break;
  case GL_DEBUG_SEVERITY_MEDIUM:
    len += sprintf_s(Buf + len, 1000, "Severity: medium");
    break;
  case GL_DEBUG_SEVERITY_LOW:
    len += sprintf_s(Buf + len, 1000, "Severity: low");
    break;
  case GL_DEBUG_SEVERITY_NOTIFICATION:
    len += sprintf_s(Buf + len, 1000, "Severity: notification");
    break;
  }
  len += sprintf_s(Buf + len, 1000, "\n\n");

  OutputDebugString(Buf);
} /* End of 'glDebugOutput' function */

/* Project namespace */
namespace dpgl
{
  /* Constructor function.
   * ARGUMENTS:
   *   - handle window
   *       HWND &hWnd;
   *   - window size
   *       INT &W, INT &H;
   */
  render::render( HWND &hWnd, INT &W, INT &H ) :
    hWnd(hWnd), FrameW(W), FrameH(H), hDC(GetDC(hWnd)), CurrentCS(cs::WORLD), CurrentFill(fill::SOLID),
    //Cam(0.1, 0.1, 100, vec3(8, 2, 8), vec3(0, 0, 0), vec3(0, 1, 0))
    Cam(0.1, 0.1, 1000, vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0))
  {
    /* Old variant */
    INT i;
    PIXELFORMATDESCRIPTOR pfd = {0};

    /* New variant */
    INT PixelFormatID;
    UINT NumOfFormats;

    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormat = NULL;
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribs = NULL;

    /* Attributes array */
    INT PixelAttribs[] =
    {
      WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
      WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
      WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
      WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
      WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
      WGL_COLOR_BITS_ARB, 32,
      WGL_ALPHA_BITS_ARB, 8,
      WGL_DEPTH_BITS_ARB, 24,
      WGL_STENCIL_BITS_ARB, 8,
      WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
      WGL_SAMPLES_ARB, 4,
      0
    };
    INT ContextAttribs[] =
    {
      WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
      WGL_CONTEXT_MINOR_VERSION_ARB, 2,
      // WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
      WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
      0
    };
    HGLRC hRC;

    /* OpenGL initialization */
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 32;
    i = ChoosePixelFormat(hDC, &pfd);
    DescribePixelFormat(hDC, i, sizeof(pfd), &pfd);
    SetPixelFormat(hDC, i, &pfd);

    /* OpenGL init: setup rendering context */
    hGLRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hGLRC);

    if (glewInit() != GLEW_OK ||
        !(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
    {
      MessageBox(hWnd, "Error OpenGL initialization", "ERROR",
        MB_ICONERROR | MB_OK);
      exit(0);
    }

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
    glDebugMessageCallback(glDebugOutput, NULL);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);

    /* New issue */
    wglCreateContextAttribs =
      (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
    wglChoosePixelFormat =
      (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");

    wglChoosePixelFormat(hDC, PixelAttribs, NULL, 1, &PixelFormatID, &NumOfFormats);
    DescribePixelFormat(hDC, PixelFormatID, sizeof(pfd), &pfd);
    SetPixelFormat(hDC, PixelFormatID, &pfd);

    hRC = wglCreateContextAttribs(hDC, 0, ContextAttribs);

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hGLRC);
    hGLRC = hRC;
    wglMakeCurrent(hDC, hGLRC);
    if (glewInit() != GLEW_OK)
      exit(0);

    PFNWGLSWAPINTERVALEXTPROC wglSwapInterval = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
    wglSwapInterval(0);

    /* Render parameters setup */
    glClearColor(0.30, 0.47, 0.8, 1);
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(-1);

    Cam.SetProj(W, H);
    ShaderCreate("DEFAULT");
  } /* End of 'render::render' function */

  /* Destructor function.
   * ARGUMENTS: None.
   */
  render::~render( VOID )
  {
  } /* End of 'render::~render' function */

  /* Resize function.
   * ARGUMENTS:
   *   - new size:
   *       INT NewW, INT NewH;
   * RETURNS: None.
   */
  VOID render::Resize( INT NewW, INT NewH )
  {
    Cam.SetProj(NewW, NewH);
    glViewport(0, 0, NewW, NewH);
  } /* End of 'render::Resize' function */

  /* Start frame draw function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID render::FrameStart( VOID )
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  } /* End of 'render::FrameStart' function */

  /* End frame draw function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID render::FrameEnd( VOID )
  {
    glFinish();
  } /* End of 'render::FrameEnd' function */

  /* Copy frame function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID render::FrameCopy( VOID )
  {
    wglSwapLayerBuffers(hDC, WGL_SWAP_MAIN_PLANE);
  } /* End of 'render::FrameCopy' function */

  /* Set new 'cs' function.
   * ARGUMENTS:
   *   - new coordinate system type:
   *       cs NewCS;
   * RETURNS: None.
   */
  VOID render::Set( cs NewCS )
  {
    CurrentCS = NewCS;
    CSStack.clear();
  } /* End of 'render::Set' function */

  /* Set new 'fill' function.
   * ARGUMENTS:
   *   - new fill type:
   *       fill NewFill;
   * RETURNS: None.
   */
  VOID render::Set( fill NewFill )
  {
    CurrentFill = NewFill;
    FillStack.clear();
  } /* End of 'render::Set' function */

  /* Push new 'cs' to queue function.
   * ARGUMENTS:
   *   - new coordinate system type:
   *       cs NewCS;
   * RETURNS: None.
   */
  VOID render::Push( cs NewCS )
  {
    CSStack.push_back(CurrentCS);
    CurrentCS = NewCS;
  } /* End of 'render::Push' function */

  /* Pop last 'cs' from queue function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID render::PopCS( VOID )
  {
    assert(CSStack.empty());
    CurrentCS = CSStack.back();
    CSStack.pop_back();
  } /* End of 'render::PopCS' function */

  /* Push new 'fill' to queue function.
   * ARGUMENTS:
   *   - new fill type:
   *       fill NewFill;
   * RETURNS: None.
   */
  VOID render::Push( fill NewFill )
  {
    FillStack.push_back(CurrentFill);
    CurrentFill = NewFill;
  } /* End of 'render::Push' function */

  /* Pop last 'fill' from queue function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID render::PopFill( VOID )
  {
    assert(FillStack.empty());
    CurrentFill = FillStack.back();
    FillStack.pop_back();
  } /* End of 'render::PopFill' function */

  /* Draw primitive.
   * ARGUMENTS:
   *   - primitive:
   *       prim *Pr;
   *   - world matrix:
   *       matr World;
   * RETURNS: None.
   */
  VOID render::Draw( prim *Pr, matr World )
  {
    //glLoadMatrixf(matr::Scale(vec3(0.01)) * Cam.MatrVP);
    //glLoadMatrixf(matr::Scale(vec3(0.01)) * Cam.MatrVP);
    glLoadMatrixf(Cam.MatrVP);
    matr WVP = World * Cam.MatrVP;
    INT loc;
    //UINT prg = ShaderCreate("DEFAULT")->prg;
    //glUseProgram(prg);
    /*if ((loc = glGetUniformLocation(prg, "MatrWVP")) != -1)
      glUniformMatrix4fv(loc, 1, FALSE, WVP);*/
    /*
    if ((loc = glGetUniformLocation(prg, "Time")) != -1)
      glUniformMatrix4fv(loc, 1, FALSE, A);
    */
    if (!Pr->NumOfI)
    {
      glBindVertexArray(Pr->VA);
      glDrawArrays(GL_TRIANGLES, 0, Pr->NumOfV);
      glBindVertexArray(0);
    }
    else
    {
      glBindVertexArray(Pr->VA);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
      glDrawElements(GL_TRIANGLES, Pr->NumOfI, GL_UNSIGNED_INT, NULL);
      glBindVertexArray(0);
    }
    glUseProgram(0);
  } /* End of 'render::Draw' function */

  /* Draw primitives.
   * ARGUMENTS:
   *   - primitives:
   *       prims &Prs;
   *   - world matrix:
   *       matr World;
   * RETURNS: None.
   */
  VOID render::Draw( prims &Prs, matr World )
  {
    Prs.Prims.Walk([this, &World]( prim &Pr ){ Draw(&Pr, World); });
  } /* End of 'render::Draw' function */
} /* end of 'dpgl' namespace */

/* END OF 'render.cpp' FILE */

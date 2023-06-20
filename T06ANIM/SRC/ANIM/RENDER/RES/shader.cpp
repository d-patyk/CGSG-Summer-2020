/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : shader.cpp
 * PURPOSE     : Shader module.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#include "shader.h"

/* Project namespace */
namespace dpgl
{
  /* Constructor function.
   * ARGUMENTS:
   *   - shader file name prefix:
   *       const std::string &FileNamePrefix;
   */
  shader::shader( const std::string &FileNamePrefix ) : Name(FileNamePrefix), prg(0)
  {
    struct
    {
      std::string Name; /* Shader file suffix name */
      INT Type;         /* Shader OpenGL type */
      INT Id;           /* Shader Id created by OpenGL */
    } shd[] =
    {
      {"vert", GL_VERTEX_SHADER},
      {"frag", GL_FRAGMENT_SHADER}
    };

    INT res, Ns = sizeof(shd) / sizeof(shd[0]);
    BOOL is_ok = TRUE;
    static GLchar Buf[10000];
    for (int i = 0; i < Ns; i++)
    {
      /* Load shader text from file */
      std::ifstream F("BIN/SHADERS/" + FileNamePrefix + "/" + shd[i].Name + ".glsl");
      std::string txt((std::istreambuf_iterator<CHAR>(F)), (std::istreambuf_iterator<CHAR>()));

      if (txt.empty())
      {
        Log(FileNamePrefix, shd[i].Name, "Your shader is empty. Check it. Pls-pls-pls, I want this shader...");
        is_ok = FALSE;
        break;
      }
      /* Create shader */
      if ((shd[i].Id = glCreateShader(shd[i].Type)) == 0)
      {
        Log(FileNamePrefix, shd[i].Name, "I want to create shader... help me, I can't...");
        is_ok = FALSE;
        break;
      }
      /* Attach shader source code to shader */
      const CHAR *txt_= txt.c_str();
      glShaderSource(shd[i].Id, 1, &txt_, NULL);
      /* Compile shader */
      glCompileShader(shd[i].Id);
      glGetShaderiv(shd[i].Id, GL_COMPILE_STATUS, &res);
      if (res != 1)
      {
        glGetShaderInfoLog(shd[i].Id, sizeof(Buf), &res, Buf);
        Log(FileNamePrefix, shd[i].Name, "GL wants to say you smth: " + std::string(Buf));
        is_ok = FALSE;
        break;
      }
    }
    if (is_ok)
    {
      if ((prg = glCreateProgram()) == 0)
      {
        is_ok = FALSE;
        Log(FileNamePrefix, "PROG", "OpenGL & AS1 aren't my friends anymore, because they don't create program for me :(");
      }
      else
      {
        /* Attach shaders to program */
        for (int i = 0; i < Ns; i++)
          glAttachShader(prg, shd[i].Id);
        glLinkProgram(prg);
        glGetProgramiv(prg, GL_LINK_STATUS, &res);
        if (res != 1)
        {
          glGetProgramInfoLog(prg, sizeof(Buf), &res, Buf);
          Log(FileNamePrefix, "PROG", "GL wants to say you smth: " + std::string(Buf));
        }
      }
    }
    /* Error handle */
    if (!is_ok)
    {
      /* Remove all shaders */
      for (int i = 0; i < Ns; i++)
        if (shd[i].Id != 0)
        {
          if (prg != 0)
            glDetachShader(prg, shd[i].Id);
          glDeleteShader(shd[i].Id);
        }
      /* Remove program */
      if (prg != 0)
        glDeleteProgram(prg);
      prg = 0;
    }
  } /* End of 'shader::shader' function */

  /* Destructor function.
   * ARGUMENTS: None.
   */
  shader::~shader( VOID )
  {
    UINT shdrs[5];
    INT n;

    if (prg == 0)
      return;
    glGetAttachedShaders(prg, 5, &n, shdrs);
    for (auto i : shdrs)
    {
      glDetachShader(prg, i);
      glDeleteShader(i);
    }
    glDeleteProgram(prg);
  } /* End of 'shader::~shader' function */

  /* Shader logger function.
   * ARGUMENTS:
   *   - file prefix, shader type:
   *       const std::string &FileNamePrefix, const std::string &Type;
   *   - error message:
   *       const std::string &Error;
   * RETURNS: None.
   */
  VOID shader::Log( const std::string &FileNamePrefix, const std::string &Type, const std::string &Error )
  {
    std::ofstream("DPGL_SHADER.LOG", std::ios::app) << "BIN/SHADERS/" + FileNamePrefix + "/" + Type + ".glsl:\n  " + Error << std::endl << std::endl;
  } /* End of 'shader::Log' function */
} /* end of 'dpgl' namespace */

/* END OF 'shader.cpp' FILE */

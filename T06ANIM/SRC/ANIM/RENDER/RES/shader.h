/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : shader.h
 * PURPOSE     : Shader module header.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#ifndef __shader_h_
#define __shader_h_
#include <string>
#include <fstream>
#include "resdef.h"


/* Project namespace */
namespace dpgl
{
  /* Shader class */
  class shader
  {
    friend material;
  public:
    const std::string Name;
  private:
    UINT prg;

  public:
    /* Constructor function.
     * ARGUMENTS:
     *   - shader file name prefix:
     *       const std::string &FileNamePrefix;
     */
    shader( const std::string &FileNamePrefix );

    /* Destructor function.
     * ARGUMENTS: None.
     */
    ~shader( VOID );

  private:
    /* Shader logger function.
     * ARGUMENTS:
     *   - file prefix, shader type:
     *       const std::string &FileNamePrefix, const std::string &Type;
     *   - error message:
     *       const std::string &Error;
     * RETURNS: None.
     */
    static VOID Log( const std::string &FileNamePrefix, const std::string &Type, const std::string &Error );
  }; /* End of 'shader' class */

  /* Shader manager class */
  class shader_manager : private resource_manager<shader>
  {
  public:
    /* Create shader function.
     * ARGUMENTS:
     *   - shader file name prefix:
     *       const std::string &FileNamePrefix;
     * RETURNS:
     *   (shader *) created shader interface.
     */
    shader * ShaderCreate( const std::string &FileNamePrefix )
    {
      shader *shd = Find(FileNamePrefix);
      if (shd == nullptr)
        Add(shd = new shader(FileNamePrefix));
      return shd;
    } /* End of 'ShaderCreate' function */
  }; /* End of 'shader_manager' class */
} /* end of 'dpgl' namespace */

#endif /* __shader_h_ */

/* END OF 'shader.h' FILE */

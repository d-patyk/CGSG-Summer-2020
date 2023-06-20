/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : material.h
 * PURPOSE     : Material module header.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#ifndef __material_h_
#define __material_h_
#include <string>
#include "texture.h"
#include "shader.h"
#include "resdef.h"

/* Project namespace */
namespace dpgl
{
  /* Material representation type */
  class material
  {
  public:
    std::string Name; /* Material name */

    /* Illumination coefficients */
    vec3 Ka, Kd, Ks; /* Ambient, diffuse, specular coefficients */
    FLT Ph;          /* Phong power coefficient */
    FLT Trans;       /* Transparency factor */
    texture *Tex[8]; /* Texture references from texture table */

    shader *Shd; /* Shader pointer */

    /* Constructor function.
     * ARGUMENTS: None.
     */
    material( VOID );

    /* Constructor function.
     * ARGUMENTS:
     *   - params:
     *       const vec3 Ka, const vec3 Kd, const vec3 Ks, const FLT Ph,
     *       const FLT Trans, texture *Tex = nullptr, shader *Shd = nullptr;
     */
    material( const vec3 Ka, const vec3 Kd, const vec3 Ks, const FLT Ph, const FLT Trans, texture *Tex = nullptr, shader *Shd = nullptr );

    /* Apply material function.
     * ARGUMENTS:
     *   - material pointer:
     *       material *Mat;
     * RETURNS: None.
     */
    VOID Apply( material *Mat );
  }; /* End of 'material' class */

  /* Material manager class */
  class material_manager : private resource_manager<material>
  {
  public:
    /* Create material function.
     * ARGUMENTS:
     *   - params:
     *       const vec3 Ka, const vec3 Kd, const vec3 Ks, const FLT Ph,
     *       const FLT Trans, texture *Tex = nullptr, shader *Shd = nullptr;
     * RETURNS:
     *   (material *) created material interface.
     */
    material * MaterialCreate( const vec3 Ka, const vec3 Kd, const vec3 Ks, const FLT Ph, const FLT Trans, texture *Tex = nullptr, shader *Shd = nullptr );
  }; /* End of 'material_manager' class */
} /* end of 'dpgl' namespace */

#endif /* __material_h_ */

/* END OF 'material.h' FILE */

/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : material.cpp
 * PURPOSE     : Material module.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#include "material.h"

/* Project namespace */
namespace dpgl
{
  /***
   * 'material' class
   ***/

  /* Constructor function.
   * ARGUMENTS: None.
   */
  material::material( VOID ) :
    Ka(0), Kd(0), Ks(0), Ph(0), Trans(0), Tex{nullptr}, Shd(nullptr)
  {
  } /* End of 'material::material' function */

  /* Constructor function.
   * ARGUMENTS:
   *   - params:
   *       const vec3 Ka, const vec3 Kd, const vec3 Ks, const FLT Ph,
   *       const FLT Trans, texture *Tex = nullptr, shader *Shd = nullptr;
   */
  material::material( const vec3 Ka, const vec3 Kd, const vec3 Ks, const FLT Ph, const FLT Trans, texture *NewTex, shader *Shd ) :
    Ka(Ka), Kd(Kd), Ks(Ks), Ph(Ph), Trans(Trans), Tex{nullptr}, Shd(Shd)
  {
    if (NewTex != nullptr)
      CopyMemory(Tex, NewTex, sizeof(texture *) * 8);
  } /* End of 'material::material' function */

  /* Apply material function.
   * ARGUMENTS:
   *   - material pointer:
   *       material *Mat;
   * RETURNS: None.
   */
  VOID material::Apply( material *Mat )
  {
    //UINT prg = Shd != nullptr ? Shd->prg : shader_manager::GetDefault();
    //glUseProgram(Mat->Shd->prg);
  } /* End of 'material::Apply' function */


  /***
   * 'material_manager' class
   ***/

  /* Create material function.
   * ARGUMENTS:
   *   - params:
   *       const vec3 Ka, const vec3 Kd, const vec3 Ks, const FLT Ph,
   *       const FLT Trans, texture *Tex = nullptr, shader *Shd = nullptr;
   * RETURNS:
   *   (material *) created material interface.
   */
  material * material_manager::MaterialCreate( const vec3 Ka, const vec3 Kd, const vec3 Ks, const FLT Ph, const FLT Trans, texture *Tex, shader *Shd )
  {
    material *mat;
    Add(mat = new material(Ka, Kd, Ks, Ph, Trans, Tex, Shd));
    return mat;
  } /* End of 'material_manager::MaterialCreate' function */

} /* end of 'dpgl' namespace */

/* END OF 'material.cpp' FILE */

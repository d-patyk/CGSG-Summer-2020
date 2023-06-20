/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : texture.cpp
 * PURPOSE     : Texture module.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#include "texture.h"

/* Project namespace */
namespace dpgl
{
  /* Constructor function.
   * ARGUMENTS:
   *   - image:
   *       image &img;
   */
  texture( const image &img );
  texture::texture
  {
    image Img(FileName);

  W = Img.W;
  H = Img.H;

  glGenTextures(1, &TexNo);
  glBindTexture(GL_TEXTURE_2D, TexNo);
  if (Img.RowsD.size() != 0)
  {
    INT levels = log(mth::Max(W, H)) / log(2) + 1;

    glTexStorage2D(GL_TEXTURE_2D, levels, GL_RGBA8, W, H);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, W, H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Img.RowsD[0]);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //gluBuild2DMipmaps(GL_TEXTURE_2D, 4, W, H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Img.RowsD[0]);
  }

} /* end of 'dpgl' namespace */

/* END OF 'texture.cpp' FILE */

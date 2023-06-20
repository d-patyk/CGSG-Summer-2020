/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : prim.h
 * PURPOSE     : Primitive module header.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#ifndef __prim_h_
#define __prim_h_
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include "TOPO/topology.h"
#include "material.h"

/* Project namespace */
namespace dpgl
{
  /* Primitive type */
  class prim
  {
  public:
    /* Primitive type */
    prim_type Type;
    /* Buffers and NOE */
    UINT VA, VBuf, IBuf, NumOfElements, NumOfV, NumOfI;
    /* Primitive transform matrix */
    matr Transform;
    /* Min and max primitive coordinates */
    vec3 Min, Max;
    /* Material */
    material *Mtl;

    /* Constructor function.
     * ARGUMENTS:
     *   - topology:
     *       const topology::base<vertex_type> &Topo;
     */
    template<typename vertex_type>
      prim( const topology::base<vertex_type> &Topo, material *Mtl = nullptr ) : Type(Topo.PrimType), NumOfV(Topo.Vertex.size()), NumOfI(Topo.Index.size()), Mtl(Mtl)
      {
        NumOfElements = NumOfI ? NumOfI : NumOfV ? NumOfV : 1;
        if (NumOfV)
        {
          glGenBuffers(1, &VBuf);
          glGenVertexArrays(1, &VA);
  
          glBindVertexArray(VA);
          glBindBuffer(GL_ARRAY_BUFFER, VBuf);
  
          glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_type) * NumOfV, &Topo.Vertex[0], GL_STATIC_DRAW);
  
          //glBindBuffer(GL_ARRAY_BUFFER, VBuf);
  
          glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(vertex_type), (VOID *)0);
          glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(vertex_type), (VOID *)sizeof(vec3));
          glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(vertex_type), (VOID *)(sizeof(vec3) + sizeof(vec2)));
          glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(vertex_type), (VOID *)(sizeof(vec3) * 2 + sizeof(vec2)));
          glEnableVertexAttribArray(0);
          glEnableVertexAttribArray(1);
          glEnableVertexAttribArray(2);
          glEnableVertexAttribArray(3);
  
          glBindVertexArray(0);
        }
        if (NumOfI)
        {
          glGenBuffers(1, &IBuf);
  
          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
          glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NumOfI, &Topo.Index[0], GL_STATIC_DRAW);
        }
        Transform = mth::matr<FLT>::Identity();
      } /* End of 'prim' function */

    /* Destructor function.
     * ARGUMENTS: None.
     */
    ~prim( VOID )
    {
      if (NumOfV)
      {
        glBindVertexArray(VA);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &VBuf);
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &VA);
      }
      if (NumOfI)
      {
        glDeleteBuffers(1, &IBuf);
      }
    } /* End of '~prim' function */
  }; /* End of 'prim' type */

  /* Primitives type */
  class prims
  {
  public:
    /* Primitive stock */
    stock<prim> Prims;

    /* Constructor function.
     * ARGUMENTS: None.
     */
    prims( VOID );

    /* Constructor function.
     * ARGUMENTS:
     *   - file name:
     *       const std::string &FileName;
     */
    prims( const std::string &FileName );

    /* Destructor function.
     * ARGUMENTS: None.
     */
    ~prims( VOID );

    /* Operator '<<' redefenition function.
     * ARGUMENTS:
     *   - new element:
     *       const Type &X;
     * RETURNS:
     *   (stock &) stock link.
     */
    prims & operator<<( prim *Pr );

    /* Operator 'stock<prim *>' redefinition function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (stock<prim *>) primitives stock.
     */
    operator stock<prim>( VOID );
  }; /* End of 'prims' type */

  /* Primitive manager */
  class primitive_manager : public resource_manager<prim>
  {
  }; /* End of 'primitive_manager' class */
} /* end of 'dpgl' namespace */

#if 0
#include <filesystem>
class file_parser
{
private:
  BYTE *Mem = nullptr;
  std::basic_string<BYTE> Content;
  std::basic_ifstream<BYTE> FileRef;
  INT RestSize;
public:

  file_parser( const std::string &FileName )
  {
    RestSize = std::filesystem::file_size(FileName);
    FileRef = std::basic_ifstream<BYTE>(FileName, std::ios::binary); /* Doing smth */
 
    Content.resize(RestSize);
    FileRef.read(Content.data(), RestSize);

    RestSize = Content.length(); /* doing smth other from other */

    Mem = Content.data(); /* doing smth what AS1 said */

  }
  operator bool( void )
  {
    return bool(FileRef);
  }
  template<class Type>
    bool Read( Type *Ptr, int N = 1)
    {
      int size = sizeof(Type) * N;

      if (RestSize < size)
        return false;

      CopyMemory(Ptr, Mem, size);
      Mem += size;
      RestSize -= size;
      return true;
    }
};
#endif /* 0 */

#endif /* __prim_h_ */

/* END OF 'prim.h' FILE */

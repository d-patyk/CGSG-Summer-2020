/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : topology.h
 * PURPOSE     : Topology module header.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#ifndef __topology_h_
#define __topology_h_
#include "../../../../def.h"

/* Project namespace */
namespace dpgl
{
  /* Primitive type enum */
  enum struct prim_type
  {
    TRIMESH,
    TRISTRIP
  }; /* End of 'prim_type' enum */

  /* Vertex namespace*/
  namespace vertex
  {
    /* Standart vertex class */
    class std
    {
    public:
      vec3 P;                   /* Point coordinates */
      vec2 T;                   /* Texture coordinates */
      vec3 N;                   /* Normal coordinates */
      vec4 C;                   /* Color */
      static const char *Descr; /* Text vertex description */

      /* Constructor function.
       * ARGUMENTS:
       *   - parameters:
       *       const vec3 &P, const vec2 &T,
       *       const vec3 &N, const vec4 &C;
       */
      std( const vec3 &P, const vec2 &T, const vec3 &N, const vec4 &C ) :
        P(P), T(T), N(N), C(C)
      {
      } /* End of 'std' function */

      std ( VOID ) : P(0), T(0), N(0), C(0)
      {
      }
    }; /* End of 'std' class */
  } /* end of 'vertex' namespace */

  /* Topology namespace */
  namespace topology
  {
    /* Base topology class */
    template<typename VertexType>
      class base
      {
      public:
        /* Primitives type */
        prim_type PrimType = prim_type::TRIMESH;
        /* Vertex stock */
        stock<VertexType> Vertex;
        /* Index stock */
        stock<INT> Index;

        /* Constructor function.
         * ARGUMENTS: None.
         */
        base( VOID )
        {
        } /* End of 'base' function */

        /* Constructor function.
         * ARGUMENTS:
         *   - new primitive type:
         *       prim_type NewPrimType;
         *   - vertex stock link:
                 const stock<VertexType> &V = {};
         *   - index stock link:
                 const stock<INT> &I = {};
         */
        base( prim_type NewPrimType, const stock<VertexType> &V = {}, const stock<INT> &I = {} ) :
          PrimType(NewPrimType), Vertex(V), Index(I)
        {
        } /* End of 'base' function */
      }; /* End of 'base' class */

    /* Trimesh topology class */
    template<typename VertexType>
      class trimesh : public base<VertexType>
      {
      public:
        /* Constructor function.
         * ARGUMENTS: None.
         */
        trimesh( VOID )
        {
        } /* End of 'trimesh' function */

        /* Constructor function.
         * ARGUMENTS:
         *   - vertex stock link:
                 const stock<VertexType> &V;
         *   - index stock link:
                 const stock<INT> &I = {};
         */
        trimesh( const stock<VertexType> &V, const stock<INT> &I = {} ) : base(prim_type::TRIMESH, V, I)
        {
        } /* End of 'trimesh' function */
        //EvalNormals???
      }; /* End of 'trimesh' class */

    /* Grid topology class */
    template<typename VertexType>
      class grid : public base<VertexType>
      {
      public:
        /* Grid size */
        INT W, H;

        /* Constructor function.
         * ARGUMENTS:
         *   - grid size:
         *       INT W, INT H;
         */
        grid( INT W, INT H ) : base<VertexType>(prim_type::TRISTRIP), W(W), H(H)
        {
          this->Vertex.resize(W * H);
        } /* End of 'grid' function */

        //EvalNormals???

        /* Operator '[]' redefinition function.
         * ARGUMENTS:
         *   - row index:
         *       INT Row;
         * RETURNS:
         *   (VertexType *) vertex pointer.
         */
        VertexType * operator[]( INT Row )
        {
          return &(this->Vertex)[Row * W];
        } /* End of 'operator[]' function */
      }; /* End of 'grid' class */

    /* Sphere topology class */
    template<typename VertexType>
      class sphere : public grid<VertexType>
      {
      public:
        /* Constructor function.
         * ARGUMENTS: None.
         */
        sphere( VOID )
        {
        } /* End of 'sphere' function */

        /* Constructor function.
         * ARGUMENTS:
         *   - sphere center:
         *       const vec3 &Center;
         *   - sphere radius:
         *       FLT R;
         *   - sphere grid size:
         *       INT W, INT H;
         */
        sphere( const vec3 &Center, FLT R, INT W, INT H ) : grid(W, H)
        {
        } /* End of 'sphere' function */
      }; /* End of 'sphere' class */
  } /* end of 'topology' namespace */
} /* end of 'dpgl' namespace */

#endif /* __topology_h_ */

/* END OF 'topology.h' FILE */

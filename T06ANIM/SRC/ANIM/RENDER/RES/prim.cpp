/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : prim.cpp
 * PURPOSE     : Primitive module.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#include "../../anim.h"

/* Project namespace */
namespace dpgl
{
  /* Constructor function.
   * ARGUMENTS: None.
   */
  prims::prims( VOID )
  {
  } /* End of 'prims::prims' function */

  /* Constructor function.
   * ARGUMENTS:
   *   - file name:
   *       const std::string &FileName;
   */
  prims::prims( const std::string &FileName )
  {
    BYTE *mem, *ptr;
    INT flen, p; //, t, m;
    FILE *F;
    DWORD Sign; /* == "G3DM" */
    INT NumOfPrims;
    INT NumOfMaterials;
    INT NumOfTextures;
    struct tagG3DMMTL
    {
      CHAR Name[300]; /* Material name */
      /* Illumination coefficients */
      vec3 Ka, Kd, Ks;    /* Ambient, diffuse, specular coefficients */
      FLT Ph;             /* Phong power coefficient - shininess */
      FLT Trans;          /* Transparency factor */
      DWORD Tex[8];       /* Texture references
                           * (8 time: texture number in G3DM file, -1 if no texture) */
      /* Shader information */
      CHAR ShaderString[300]; /* Additional shader information */
      DWORD ShdNo;       /* Shader number (uses after load into memory) */
    }; // *mtls;

    /* Open file */
    if ((F = fopen(FileName.c_str(), "rb")) == NULL)
      return;

    /* Obtain file length */
    fseek(F, 0, SEEK_END);
    flen = ftell(F);
    rewind(F);

    /* Allocate memory and load whole file to memory */
    mem = new BYTE[flen];

    fread(mem, 1, flen, F);
    fclose(F);

    ptr = mem;

    Sign = *(DWORD *)ptr, ptr += 4;
    if (Sign != *(DWORD *)"G3DM")
    {
      delete[] mem;
      return;
    }
    NumOfPrims = *(DWORD *)ptr, ptr += 4;
    NumOfMaterials = *(DWORD *)ptr, ptr += 4;
    NumOfTextures = *(DWORD *)ptr, ptr += 4;

    Prims.reserve(NumOfPrims);

    /* Primitives */
    for (p = 0; p < NumOfPrims; p++)
    {
      DWORD NumOfVertexes; /* Num of vertexes */
      DWORD NumOfIndexes;  /* Num of indexes */
      INT MtlNo;           /* Material number in table below (in material section) */
      vertex::std *V;      /* Vertexes pointer */
      INT *Ind;            /* Indexes pointer */

      NumOfVertexes = *(DWORD *)ptr, ptr += 4;
      NumOfIndexes = *(DWORD *)ptr, ptr += 4;
      MtlNo = *(INT *)ptr, ptr += 4;
      V = (vertex::std *)ptr, ptr += sizeof(vertex::std) * NumOfVertexes;
      Ind = (INT *)ptr, ptr += sizeof(INT) * NumOfIndexes;
      Prims.emplace_back(topology::base<vertex::std>(
        prim_type::TRIMESH,
        stock<vertex::std>(V, V + NumOfVertexes),
        stock<INT>(Ind, Ind + NumOfIndexes)));

      /*topology::base<vertex::std> x = topology::base<vertex::std>(
        prim_type::TRIMESH,
        stock<vertex::std>(V, V + NumOfVertexes),
        stock<INT>(Ind, Ind + NumOfFacetIndexes));*/
      // Prs->Prims[p].MtlNo = MtlNo + VI6_RndMaterialsSize;
    }

#if 0
    /* Materials */
    mtls = (struct tagG3DMMTL *)ptr, ptr += sizeof(struct tagG3DMMTL) * NumOfMaterials;
    for (m = 0; m < NumOfMaterials; m++)
    {
      INT i;
      vi6MATERIAL mtl = VI6_RndMtlGetDef();

      strncpy(mtl.Name, mtls[m].Name, VI6_STR_MAX - 1);
      mtl.Ka = mtls[m].Ka;
      mtl.Kd = mtls[m].Kd;
      mtl.Ks = mtls[m].Ks;
      mtl.Ph = mtls[m].Ph;
      mtl.Trans = mtls[m].Trans;
      for (i = 0; i < 8; i++)
        mtl.Tex[i] = (mtls[m].Tex[i] == -1 ? -1 : mtls[m].Tex[i] + VI6_RndTexturesSize);
      VI6_RndMtlAdd(&mtl);
    }

    /* Textures */
    for (t = 0; t < NumOfTextures; t++)
    {
      struct
      {
        CHAR Name[300]; /* Texture name */
        DWORD W, H;     /* Texture image size in pixels */
        DWORD C;        /* Texture image components (1-mono, 3-bgr or 4-bgra) */
      } *tex = (VOID *)ptr;

      ptr += sizeof(*tex);
      VI6_RndTexAddImg(tex->Name, tex->W, tex->H, tex->C, ptr);
      ptr += tex->W * tex->H * tex->C;
    }
#endif

    delete[] mem;
  } /* End of 'prims::prims' function */

  /* Destructor function.
   * ARGUMENTS: None.
   */
  prims::~prims( VOID )
  {
    //Prims.Walk([]( prim *pr ){ delete pr; });
  } /* End of 'prims::~prim' function */

  /* Operator '<<' redefenition function.
   * ARGUMENTS:
   *   - new element:
   *       const Type &X;
   * RETURNS:
   *   (stock &) stock link.
   */
  prims & prims::operator<<( prim *Pr )
  {
    Prims << *Pr;

    return *this;
  } /* End of 'prims::operator<<' function */

  /* Operator 'stock<prim *>' redefinition function.
   * ARGUMENTS: None.
   * RETURNS:
   *   (stock<prim *>) primitives stock.
   */
  prims::operator stock<prim>( VOID )
  {
    return Prims;
  } /* End of 'prims::operator stock<prim *>' function */
} /* end of 'dpgl' namespace */

/* END OF 'prim.cpp' FILE */

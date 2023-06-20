/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : topology.cpp
 * PURPOSE     : Topology module.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#include "topology.h"
#include "../../../../def.h"

/* Project namespace */
namespace dpgl
{
  const char *vertex::std::Descr = "f3f2f3f4";
  topology::grid<vertex::std> test(5, 6);
} /* end of 'dpgl' namespace */


/* END OF 'topology.cpp' FILE */

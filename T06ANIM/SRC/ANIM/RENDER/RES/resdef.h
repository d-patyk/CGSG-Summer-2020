/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : resdef.h
 * PURPOSE     : Resource base header.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#ifndef __resdef_h_
#define __resdef_h_
#include <string>
#include "../../../def.h"

/* Project namespace */
namespace dpgl
{
  class prim;
  class material;
  class shader;
  class texture;
  /* Resource manager class */
  template<class type>
    class resource_manager
    {
    protected:
      /* Resource stock */
      stock<type *> Stock;

      /* Add resource to stock function.
       * ARGUMENTS:
       *   - resource to be add:
       *       type *Res;
       * RETURNS:
       *   (resource_manager &) self reference.
       */
      resource_manager & Add( type *Res )
      {
        Stock.push_back(Res);
        return *this;
      } /* End of 'Add' function */

      /* Destructor function.
       * ARGUMENTS: None.
       */
      ~resource_manager( VOID )
      {
        for (auto r : Stock)
          delete r;
      } /* End of '~resource_manager' function */

      /* Find resource at stock function.
       * ARGUMENTS:
       *   - resource name to find:
       *       const std::string &Name;
       * RETURNS:
       *   (type *) reference to found elememt.
       */
      type * Find( const std::string &Name )
      {
        for (auto i : Stock)
        {
          if (i->Name == Name)
            return i;
        }

        return nullptr;
      } /* End of 'Find' function */
    };
} /* end of 'dpgl' namespace */

#endif /* __resdef_h_ */

/* END OF 'resdef.h' FILE */

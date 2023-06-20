/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : stock.h
 * PURPOSE     : Stock header.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#ifndef __stock_h_
#define __stock_h_
#include <vector>
#include <commondf.h>

/* Project namespace */
namespace dpgl
{
  /* Stock class */
  template<typename Type>
    class stock : public std::vector<Type>
    {
    public:
      /* Constructor function
       * ARGUMENTS: None.
       */
      stock( VOID )
      {
      } /* End of 'stock' function */

      /* Constructor function
       * ARGUMENTS:
       *   - iterators:
       *       Iter first, Iter last;
       */
      template<class Iter>
        stock( Iter first, Iter last ) : std::vector<Type>(first, last)
        {
        } /* End of 'stock' function */

      /* Operator '<<' redefenition function.
       * ARGUMENTS:
       *   - new element:
       *       const Type &X;
       * RETURNS:
       *   (stock &) stock link.
       */
      stock & operator<<( const Type &X )
      {
        this->push_back(X);
        return *this;
      } /* End of 'operator<<' function */

      /* Stock walk function.
       * ARGUMENTS:
       *   - walker:
       *       WalkType Walk;
       * RETURNS: None.
       */
      template<class WalkType>
        VOID Walk( WalkType Walk )
        {
          for (auto &x : *this)
            Walk(x);
        } /* End of 'Walk' function*/
    }; /* End of 'stock' class */
} /* end of 'dpgl' namespace */

#endif /* __stock_h_ */

/* END OF 'stock.h' FILE */

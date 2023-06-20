/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : test.cpp
 * PURPOSE     : Test unit.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#include "../ANIM/anim.h"

/* Test unit class */
class test_unit : public dpgl::units::unit
{
private:
  dpgl::prim *Pr;
  dpgl::prims Primsss;
  dpgl::topology::base<dpgl::vertex::std> Topo;

public:
  /* Constructor function.
   * ARGUMENTS:
   *   - animation context pointer:
   *       anim *Ani;
   */
  test_unit( dpgl::anim *Ani ) : unit(Ani), Topo(), Primsss("BIN\\G3DM\\ficus.g3dm")
  {
    Topo.Vertex.resize(3);
    Topo.Vertex.push_back(dpgl::vertex::std(
      dpgl::vec3(0, 0, 0),
      dpgl::vec2(0, 0),
      dpgl::vec3(0, 0, 0),
      dpgl::vec4(1, 0, 0, 1)
    ));
    Topo.Vertex.push_back(dpgl::vertex::std(
      dpgl::vec3(0, 1, 0),
      dpgl::vec2(0, 0),
      dpgl::vec3(0, 0, 0),
      dpgl::vec4(0, 1, 0, 1)
    ));
    Topo.Vertex.push_back(dpgl::vertex::std(
      dpgl::vec3(1, 1, 0),
      dpgl::vec2(0, 0),
      dpgl::vec3(0, 0, 0),
      dpgl::vec4(0, 0, 1, 1)
    ));
    /*
    Topo.Index.push_back(0);
    Topo.Index.push_back(1);
    Topo.Index.push_back(2);
    */
    Pr = new dpgl::prim(Topo);
  } /* End of 'test_unit' function */

  /* Destructor function.
   * ARGUMENTS: None.
   */
  ~test_unit( VOID ) override
  {
    delete Pr;
  } /* End of '~test_unit' function */

  /* Response unit function.
   * ARGUMENTS:
   *   - animation context pointer:
           anim *Ani;
   * RETURNS: None.
   */
  VOID Response( dpgl::anim *Ani ) override
  {
  } /* End of 'Response' function */

  /* Render unit function.
   * ARGUMENTS:
   *   - animation context pointer:
           anim *Ani;
   * RETURNS: None.
   */
  VOID Render( dpgl::anim *Ani ) override
  {
    // Ani->Draw(Pr);
    Ani->Draw(Primsss, dpgl::matr::Scale(dpgl::vec3(0.01)));
  } /* End of 'Render' function */
}; /* End of 'test_unit' class */

/* Unit registration */
static dpgl::anim::unit_register<test_unit> _("Test");

/* END OF 'test.cpp' FILE */

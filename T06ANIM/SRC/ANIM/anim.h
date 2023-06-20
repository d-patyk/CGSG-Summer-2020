/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : anim.h
 * PURPOSE     : Animation module header.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#ifndef __anim_h_
#define __anim_h_
#include "../WIN/win.h"
#include "input.h"
#include "timer.h"
#include "RENDER/render.h"
#include <string>
#include <map>

/* Project namespace */
namespace dpgl
{
  /* Animation class declaration */
  class anim;

  /* Units namespace */
  namespace units
  {
    /* Unit class */
    class unit
    {
    public:
      /* Constructor function.
       * ARGUMENTS:
       *   - animation context pointer:
       *       anim *Ani;
       */
      unit( anim *Ani );

      /* Destructor function.
       * ARGUMENTS: None.
       */
      virtual ~unit( VOID );

      /* Response unit function.
       * ARGUMENTS:
       *   - animation context pointer:
               anim *Ani;
       * RETURNS: None.
       */
      virtual VOID Response( anim *Ani );

      /* Render unit function.
       * ARGUMENTS:
       *   - animation context pointer:
               anim *Ani;
       * RETURNS: None.
       */
      virtual VOID Render( anim *Ani );
    }; /* End of 'unit' class */

    /* Scene class */
    class scene : public unit
    {
    public:
      /* Units stock */
      stock<unit *> Units;

      /* Constructor function.
       * ARGUMENTS:
       *   - animation context pointer:
       *       anim *Ani;
       */
      scene( anim *Ani );

      /* Destructor function.
       * ARGUMENTS: None.
       */
      ~scene( VOID ) override;

      /* Response scene function.
       * ARGUMENTS:
       *   - animation context pointer:
       *       anim *Ani;
       * RETURNS: None.
       */
      VOID Response( anim *Ani ) override;

      /* Response scene function.
       * ARGUMENTS:
       *   - animation context pointer:
       *       anim *Ani;
       * RETURNS: None.
       */
      VOID Render( anim *Ani ) override;

#if 0
      /* Operator '<<' redefenition function.
       * ARGUMENTS:
       *   - new 'unit' element pointer:
       *       unit *Uni;
       * RETURNS:
       *   (scene &) scene link.
       */
      scene & operator<<( unit *Uni );
#endif

      /* Operator '<<' redefenition function.
       * ARGUMENTS:
       *   - new 'unit' name:
       *       unit *Uni;
       * RETURNS:
       *   (scene &) scene link.
       */
      scene & operator<<( const std::string &Name );
    }; /* End of 'scene' class */
  } /* end of 'units' namespace */

  /* Animation class */
  class anim : public win, public input, public timer, public render
  {
  private:
    static anim Anim; /* single tone object of class 'anim' */

    /* Animation scene pointer */
    units::unit *Scene;

    /* Is exit */
    BOOL IsExit = FALSE;

    /* Constructor function.
     * ARGUMENTS: None.
     */
    anim( VOID );

    /* Copying constructor deletion */
    anim( const anim &ani ) = delete;

    /* Operator '=' deletion */
    anim & operator=( const anim &ani ) = delete;

  public:
    /* Get single tone object of class 'anim'.
     * ARGUMENTS: None.
     * RETURNS:
     *   (anim &) anim object.
     */
    static anim & Get( VOID );

    /* Get single tone object pointer of class 'anim'.
     * ARGUMENTS: None.
     * RETURNS:
     *   (anim *) anim object pointer.
     */
    static anim * GetPtr( VOID );

    /* Render frame function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Render( VOID );

    /* Set new animation scene function.
     * ARGUMENTS:
     *   - new scene pointer:
     *       units::unit *NewScene;
     * RETURNS:
     *   (anim &) anim link.
     */
    anim & SceneSet( units::unit *NewScene );

#if 0
    /* Operator '<<' redefenition function.
     * ARGUMENTS:
     *   - new 'unit' element pointer:
     *       units::unit *Uni;
     * RETURNS:
     *   (anim &) anim link.
     */
    anim & operator<<( units::unit *Uni );
#endif

    /* Operator '<<' redefenition function.
     * ARGUMENTS:
     *   - new 'unit' name:
     *       unit *Uni;
     * RETURNS:
     *   (anim &) scene link.
     */
    anim & operator<<( const std::string &Name );

    /* Exit from program function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Exit( VOID );


    /* Init function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init( VOID ) override;

    /* Close function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Close( VOID ) override;

    /* Resize function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Resize( VOID ) override;

    /* Timer function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Timer( VOID ) override;

    /* Activate function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Activate( VOID ) override;

    /* Idle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Idle( VOID ) override;

    /* Erase function.
     * ARGUMENTS:
     *   - handle draw context
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Erase( HDC hDC ) override;

    /* Paint function.
     * ARGUMENTS:
     *   - handle draw context
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Paint( HDC hDC ) override;

    /* Map of unit names */
    std::map<std::string, units::unit * (*)( VOID )> UnitNames;

    /* Unit registration class */
    template<class UnitType>
      class unit_register
      {
      public:
        /* Create unit function
         * ARGUMENTS: None.
         * RETURNS:
         *   (unit *) new unit;
         */
        static units::unit * Create( VOID )
        {
          return new UnitType(&Anim);
        } /* End of 'Create' function */

        /* Constructor function.
         * ARGUMENTS:
         *   - unit name:
         *       const std::string &Name;
         */
        unit_register( const std::string &Name )
        {
          Anim.UnitNames[Name] = Create;
        } /* End of 'unit_register' function */
      }; /* End of 'unit_register' class */
  }; /* End of 'anim' class */
} /* end of 'dpgl' namespace */

#endif /* __anim_h_ */

/* END OF 'anim.h' FILE */

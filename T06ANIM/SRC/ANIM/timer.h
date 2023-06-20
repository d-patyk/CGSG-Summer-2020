/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : timer.h
 * PURPOSE     : Timer module header.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#ifndef __timer_h_
#define __timer_h_
#include "../def.h"

/* Project namespace */
namespace dpgl
{
  /* Timer class */
  class timer
  {
  private:
    UINT64
      StartTime,    /* Start program time */
      OldTime,      /* Previous frame time */
      OldTimeFPS,   /* Old time FPS measurement */
      PauseTime,    /* Time during pause period */
      TimePerSec,   /* Timer resolution */
      FrameCounter; /* Frames counter */
  public:
    DBL
      GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
      Time, DeltaTime,             /* Time with pause and interframe interval */
      FPS;                         /* Frames per second value */
    BOOL
      IsPause;                     /* Pause flag */

    /* Constructor function.
     * ARGUMENTS: None.
     */
    timer( VOID ) :
      StartTime(), OldTime(), OldTimeFPS(), PauseTime(0), TimePerSec(),
      FrameCounter(0), GlobalTime(), GlobalDeltaTime(), Time(),
      DeltaTime(), FPS(30.0), IsPause(FALSE)
    {
      LARGE_INTEGER t;

      QueryPerformanceFrequency(&t);
      TimePerSec = t.QuadPart;
      QueryPerformanceCounter(&t);
      StartTime = OldTime = OldTimeFPS = t.QuadPart;
    } /* End of 'timer' function */

    /* Timer response function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Response( VOID )
    {
      LARGE_INTEGER t;

      QueryPerformanceCounter(&t);

      /* Global time */
      GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
      GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;

      /* Time with pause */
      if (IsPause)
      {
        DeltaTime = 0;
        PauseTime += t.QuadPart - OldTime;
      }
      else
      {
        DeltaTime = GlobalDeltaTime;
        Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
      }

      /* FPS */
      FrameCounter++;
      if (t.QuadPart - OldTimeFPS > TimePerSec)
      {
        FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
        OldTimeFPS = t.QuadPart;
        FrameCounter = 0;
      }
      OldTime = t.QuadPart;
    } /* End of 'Response' function */
  }; /* End of 'timer' class */
} /* end of 'dpgl' namespace */

#endif /* __timer_h_ */

/* END OF 'timer.h' FILE */

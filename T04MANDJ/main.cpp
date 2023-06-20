/* FILE NAME: main.cpp
 * PROGRAMMER: DP1
 * DATE: 21.07.2020
 * PURPOSE: Draw Julia set.
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <glut.h>
#include <cmath>
#include <ctime>
#include <thread>

#define MAX_THREADS 128

/* Complex numbers representation type */
struct cmpl
{
  double re, im;  /* Complex components: real, imaginary */

  /* 'frame' struct constructor function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  cmpl( void ) : re(0), im(0)
  {
  } /* End of 'cmpl' function */

  /* 'frame' struct constructor function.
   * ARGUMENTS:
   *   - complex components:
   *       double re, im;
   * RETURNS: None.
   */
  cmpl( double re, double im ) : re(re), im(im)
  {
  } /* End of 'cmpl' function */

  /* 'frame' struct '+' operator definition function.
   * ARGUMENTS:
   *   - complex number:
   *       const cmpl &c;
   * RETURNS:
   *   (cmpl) result.
   */
  cmpl operator+( const cmpl &c )
  {
    return cmpl(this->re + c.re, this->im + c.im);
  } /* End of 'operator+' function */

  /* 'frame' struct '*' operator definition function.
   * ARGUMENTS:
   *   - complex number:
   *       const cmpl &c;
   * RETURNS:
   *   (cmpl) result.
   */
  cmpl operator*( const cmpl &c )
  {
    return cmpl(this->re * c.re - this->im * c.im, this->re * c.im + this->im * c.re);
  } /* End of 'operator*' function */

  /* 'frame' struct module(|z|) definition function.
   * ARGUMENTS: None.
   * RETURNS:
   *   (double) result.
   */
  double operator!( void )
  {
    return re * re + im * im;
  } /* End of 'operator!' function */
};

/* Frame representation type */
struct frame
{
  int w, h;              /* frame width and height */
  unsigned char *image;  /* frame data */

  /* 'frame' struct constructor function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  frame( void ) : w(0), h(0), image(nullptr)
  {
  } /* End of 'frame' function */

  /* Resize window function.
   * ARGUMENTS:
   *   - width:
   *       int W;
   *   - height:
   *       int H;
   * RETURNS: None.
   */
  void Resize( int w, int h )
  {
    if (this->w != w || this->h != h)
    {
      this->w = w, this->h = h;
      if (image != nullptr)
        delete[] image;
      image = new unsigned char[w * h * 3];
    }
  } /* End of 'Resize' function */

  /* Put pixel to frame function.
   * ARGUMENTS:
   *   - coordinates:
   *       int X, Y;
   *   - color components:
   *       int R, G, B;
   * RETURNS: None.
   */
  void Put( int X, int Y, int R, int G, int B )
  {
    if (image == nullptr)
      return;

    if (X >= 0 && Y >= 0 && X < w && Y < h)
    {
      image[Y * w * 3 + X * 3] = B;
      image[Y * w * 3 + X * 3 + 1] = G;
      image[Y * w * 3 + X * 3 + 2] = R;
    }
  } /* End of 'Put' function */
} Frame;

/* Resize window function.
 * ARGUMENTS:
 *   - width:
 *       int W;
 *   - height:
 *       int H;
 * RETURNS: None.
 */
void Resize( int W, int H )
{
  Frame.Resize(W, H);
} /* End of 'Resize' function */

/* Draw FPS function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void DrawFPS( void )
{
  static double lastUpdateTime = -1000000;
  static double FPS = 0;
  static char Buf[5000];

  double CurTime = clock() / (double)CLOCKS_PER_SEC;
  FPS++;
  if (CurTime - lastUpdateTime > 5)
  {
    sprintf_s(Buf, "FPS: %f", FPS / (CurTime - lastUpdateTime));
    FPS = 0, lastUpdateTime = CurTime;
    glutSetWindowTitle(Buf);
  }
} /* End of 'DrawFPS' function */

/* Draw pixel of fractal function.
 * ARGUMENTS:
 *   - coordinates:
 *       int x, y;
 *   - fractal parameter:
 *       cmpl c;
 */
void DrawFractalPixelRow( int y, const cmpl &c )
{
  for (int x = 0; x < Frame.w; x++)
  {
    cmpl zn(x * 4.0 / Frame.w - 2.0, y * 4.0 / Frame.h - 2.0);
    int n = 0;
    while (n < 255 && !zn < 4)
      zn = zn * zn + c, n++;
    Frame.Put(x, y, n, n / 8, n * 8);
  }
}

void DrawFractalPixelRows( int y1, int y2, const cmpl &c )
{
  for (int y = y1; y < y2; y++)
    for (int x = 0; x < Frame.w; x++)
    {
      cmpl zn(x * 4.0 / Frame.w - 2.0, y * 4.0 / Frame.h - 2.0);
      int n = 0;
      while (n < 255 && !zn < 2)
        zn = zn * zn + c, n++;
      Frame.Put(x, y, n, n / 8, n * 8);
    }
}

/* Display window function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void Display( void )
{
  static std::thread threads[MAX_THREADS];
  //std::thread *threads = new std::thread[MAX_THREADS];
  int threads_count = 0;
  //static cmpl c(1.0, 0.05);
  static cmpl c(0.39, 0.29);

  /* Очищаем окно (rgba - 0..1) */
  glClearColor(0.3, 0.5, 0.7, 0);
  glClear(GL_COLOR_BUFFER_BIT);
                                                       

  int ys = 0;
  while (ys < Frame.h)
  {
    threads[threads_count++] = std::thread(DrawFractalPixelRows, ys, fmin(ys + 128, Frame.h), c);
    ys = fmin(ys + 128, Frame.h);
  }
  for (int i = 0; i < threads_count; i++)
    threads[i].join();

  /*for (int ys = 0; ys < Frame.h; ys++)
  {
    if (threads_count == 16)
    {
      for (int i = 0; i < threads_count; i++)
        threads[i].join();
      threads_count = 0;
    }
    //threads[threads_count++] = std::thread(DrawFractalPixelRow, ys, c);
    DrawFractalPixelRow(ys, c);
  }
  for (int i = 0; i < threads_count; i++)
    threads[i].join();*/
  /*std::thread th1(DrawFractalPixelRows, 0, 127, c);
  std::thread th2(DrawFractalPixelRows, 128, 255, c);
  std::thread th3(DrawFractalPixelRows, 256, 383, c);
  std::thread th4(DrawFractalPixelRows, 384, 512, c);
  th1.join(), th2.join(), th3.join(), th4.join();*/



  /* Рисуем массив в окно */
  /* можно для масштаба: glPixelZoom(sx, sy); */
  //glPixelZoom(Scale, Scale);
  glDrawPixels(Frame.w, Frame.h, GL_BGR_EXT, GL_UNSIGNED_BYTE, Frame.image);

  /* отсылаем на рисовку */
  glFinish();          /* окончание рисовательных команд */
  glutSwapBuffers();   /* копирование фонового буфера */
  glutPostRedisplay(); /* сигнал на перерисовку */
  DrawFPS();
} /* End of 'Display' function */

/* Main function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (int) exit code.
 */
int main( void )
{
  /* Инициализация */
  //glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(512, 512);
  glutCreateWindow("10-1 forever...");

  /* Подвес на события */
  glutDisplayFunc(Display);       /* перерисовка */
  glutReshapeFunc(Resize);        /* изменение размера */

  /* запуск цикла работы */
  glutMainLoop();

  return 0;
} /* End of 'main' function */

/* END OF 'MAIN.CPP' FILE */

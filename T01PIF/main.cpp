/* FILE NAME: main.cpp
 * PROGRAMMER: DP1
 * DATE: 20.07.2020
 * PURPOSE: Draw Pifagor table.
 */
#include <iostream>
#include <cmath>

/* Draw border to console function.
 * ARGUMENTS:
 *   - border width:
 *       int width;
 * RETURNS: None.
 */
void draw_border( int width )
{
  for (int i = 0; i < width; i++)
    std::cout << '-';
  std::cout << std::endl;
} /* End of 'draw_border' function */

/* Main function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (int) exit code.
 */
int main( void )
{
  int n, cell_width;

  std::cin >> n;
  cell_width = int(ceil(log10(n * n + 1))) + 1;

  // Top border
  draw_border(cell_width * (n + 1) + 3);

  // First row
  for (int i = 0; i < cell_width; i++)
    std::cout << '*';
  std::cout << '|';
  for (int x = 1; x <= n; x++)
    std::cout.width(cell_width), std::cout << x;
  std::cout << ' ' << '|' << std::endl;

  // Middle border
  draw_border(cell_width * (n + 1) + 3);

  // Other rows
  for (int x = 1; x <= n; x++)
  {
    std::cout.width(cell_width), std::cout << x;
    std::cout << '|';
    for (int y = 1; y <= n; y++)
      std::cout.width(cell_width), std::cout << x * y;
    std::cout << ' ' << '|' << std::endl;
  }

  // Bottom border
  draw_border(cell_width * (n + 1) + 3);

  return 0;
} /* End of 'main' function */

/* END OF 'MAIN.CPP' FILE */

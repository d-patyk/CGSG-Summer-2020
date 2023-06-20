/* FILE NAME: main.cpp
 * PROGRAMMER: DP1
 * DATE: 20.07.2020
 * PURPOSE: Sort list.
 */
#include <fstream>
#include <cstdlib>

/*
template <typename Type>
  void Swap( Type &a, Type &b )
  {
    Type c;

    c = a;
    a = b;
    b = c;
  }
*/

template <typename Type>
  void MergeSortRec( Type *list, size_t n, Type *tmplist )
  {
    int n1, n2, *list1, *list2;

    if (n == 1)
      return;

    n1 = n / 2, n2 = n - n1, list1 = list, list2 = list + n1;
    MergeSortRec(list1, n1, tmplist);
    MergeSortRec(list2, n2, tmplist);

    int i = 0, j = 0, *k = tmplist;
    while (i < n1 || j < n2)
    {
      if (j >= n2)
        *k++ = list1[i], i++;
      else if (i >= n1 || list2[j] < list1[i])
        *k++ = list2[j], j++;
      else
        *k++ = list1[i], i++;
    }
    for (i = 0; i < n; i++)
      list[i] = tmplist[i];
  }

template <typename Type>
  void MergeSort( Type *list, size_t n )
  {
    Type *tmplist = (Type *)malloc(sizeof(Type) * n);
    MergeSortRec(list, n, tmplist);
    free(tmplist);
  }

/* Main function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (int) exit code.
 */
int main( void )
{
  int n, *list;
  std::fstream fin, fout;

  fin.open("file.in", std::fstream::in);
  fin >> n;
  list = (int *)malloc(sizeof(int) * n);
  for (int i = 0; i < n; i++)
    fin >> list[i];
  fin.close();

  MergeSort(list, n);

  fout.open("file.out", std::fstream::out);
  for (int i = 0; i < n; i++)
    fout << list[i] << std::endl;
  fout.close();

  free(list);

  return 0;
} /* End of 'main' function */

/* END OF 'MAIN.CPP' FILE */

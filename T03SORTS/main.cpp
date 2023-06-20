/* FILE NAME: main.cpp
 * PROGRAMMER: DP1
 * DATE: 20.07.2020
 * PURPOSE: Sort list.
 */
#include <fstream>
#include <cstdlib>

/* Array representation type */
template<typename Type>
  struct array
  {
    int length; /* List length */
    Type *list; /* List */


    /* Constructor function.
     * ARGUMENTS:
     *   - file name:
     *       std::string filename;
     * RETURNS: None.
     */
    array( std::string filename )
    {
      std::fstream fin;

      fin.open(filename, std::fstream::in);
      fin >> length;
      list = new Type[length];
      for (int i = 0; i < length; i++)
        fin >> list[i];
      fin.close();
    } /* End of 'array' function */

    /* Destructor function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    ~array( void )
    {
      delete[] list;
    } /* End of '~array' function */

    /* Merge sort recursion function.
     * ARGUMENTS:
     *   - list:
     *       Type *list;
     *   - list length:
     *       int n;
     *   - extra list:
     *       Type *tmplist;
     * RETURNS: None;
     */
    void MergeSortRec( Type *list, int n, Type *tmplist )
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
    } /* End of 'MergeSortRec' function */

    /* Merge sort function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    void MergeSort( void )
    {
      Type *tmplist = new Type[length];
      MergeSortRec(list, length, tmplist);
      delete[] tmplist;
    } /* End of 'MergeSort' function */

    /* Print list to file function.
     * ARGUMENTS:
     *   - file name:
     *       std::string filename;
     * RETURNS: None.
     */
    void out( std::string filename )
    {
      std::fstream fout;

      fout.open(filename, std::fstream::out);
      for (int i = 0; i < length; i++)
        fout << list[i] << std::endl;
      fout.close();
    } /* End of 'out' function */
  };



/* Main function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (int) exit code.
 */
int main( void )
{
  array<int> massy("file.in");

  massy.MergeSort();
  massy.out("file.out");

  return 0;
} /* End of 'main' function */

/* END OF 'MAIN.CPP' FILE */

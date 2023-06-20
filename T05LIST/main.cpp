/* FILE NAME: main.cpp
 * PROGRAMMER: DP1
 * DATE: 22.07.2020
 * PURPOSE: List class.
 */
#include <iostream>

/* Debug memory allocation support */ 
#ifndef NDEBUG 
# define _CRTDBG_MAP_ALLOC
# include <crtdbg.h> 
# define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

static class __Dummy 
{ 
public: 
  /* Class constructor */
  __Dummy( void ) 
  { 
    SetDbgMemHooks(); 
  } /* End of '__Dummy' constructor */
} __ooppss;
#endif /* _DEBUG */ 

#ifdef _DEBUG 
# ifdef _CRTDBG_MAP_ALLOC 
#   define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
# endif /* _CRTDBG_MAP_ALLOC */ 
#endif /* _DEBUG */

namespace dp1
{
  /* Linear single-connected list handle class */
  template<typename Type>
    class list
    {
    private:
      /* One list element representation type */
      class list_entry
      {
      public:
        Type Data;        /* List element data */
        list_entry *Next; /* Pointer to next list element */

        /* Constructor function.
         * ARGUMENTS:
         *   - data value:
         *       Type &NewData;
         *   - next element pointer:
         *       list_entry *NewNext;
         */
        list_entry( const Type &NewData, list_entry *NewNext = nullptr ) :
          Data(NewData), Next(NewNext)
        {
        } /* End of 'list_entry' function */
      }; /* End of 'list_entry' class */

      list_entry *Start = nullptr; // Pointer to list first element

    public:
      /* Constructor function.
       * ARGUMENTS: None.
       */
      list( void )
      {
      } /* End of 'list' function */

      /* Constructor function.
       * ARGUMENTS: None.
       */
      list( const list &NewList )
      {
        Clone(NewList);
      } /* End of 'list' function */

      /* Destructor function.
       * ARGUMENTS: None.
       */
      ~list( void )
      {
        Clear();
      } /* End of '~list' function */

      /* Add new element to list start function.
       * ARGUMENTS:
       *   - data:
       *       const Type &NewData;
       * RETURNS:
       *   (list &) self pointer to list.
       */
      list & PushFront( const Type &NewData )
      {
        Start = new list_entry(NewData, Start);

        return *this;
      } /* End of 'PushFront' function */

      /* Add new element to list end function.
       * ARGUMENTS:
       *   - data:
       *       const Type &NewData;
       * RETURNS:
       *   (list &) self pointer to list.
       */
      list & PushBack( const Type &NewData )
      {
        list_entry **ptr = &Start;

        while (*ptr != nullptr)
          ptr = &(*ptr)->Next;
        *ptr = new list_entry(NewData);

        return *this;
      } /* End of 'PushBack' function */

      /* Remove element from the front of list function.
       * ARGUMENTS:
       *   - data:
       *       Type &OldData;
       * RETURNS:
       *   (list &) self pointer to list.
       */
      bool PopFront( Type &OldData )
      {
        if (Start == nullptr)
          return false;

        OldData = Start->Data;
        list_entry *OldStart = Start;
        Start = Start->Next;
        delete OldStart;

        return true;
      } /* End of 'PopFront' function */

      /* Remove element from the end of list function.
       * ARGUMENTS:
       *   - data:
       *       Type &OldData;
       * RETURNS:
       *   (list &) self pointer to list.
       */
      bool PopBack( Type &OldData )
      {
        if (Start == nullptr)
          return false;

        list_entry **ptr = &Start;
        while ((*ptr)->Next != nullptr)
          ptr = &(*ptr)->Next;
        OldData = (*ptr)->Data;
        delete *ptr;
        *ptr = nullptr;

        return true;
      } /* End of 'PopBack' function */

      /* Print list to console function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      void Display( std::ostream &stream = std::cout )
      {
        list_entry *ptr = Start;
        stream << '{';
        while (ptr != nullptr)
        {
          stream << ptr->Data << ((ptr->Next == nullptr) ? "" : ", ");
          ptr = ptr->Next;
        }
        stream << '}';
      } /* End of 'Display' function */

      /* Clear list function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      void Clear( void )
      {
        list_entry *to_delete = Start;
        while (Start != nullptr)
        {
          Start = Start->Next;
          delete to_delete;
          to_delete = Start;
        }
      } /* End of 'Clear' function */

      /* Check is list empty function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (bool) is list empty.
       */
      bool IsEmpty( void )
      {
        if (Start == nullptr)
          return true;
        return false;
      } /* End of 'IsEmpty' function */

    private:
      /* Clone list function.
       * ARGUMENTS:
       *   - new list:
       *       const list &NewList;
       * RETURNS: None.
       */
      void Clone( const list &NewList )
      {
        Clear();
        list_entry *ptr = NewList.Start;
        list_entry **local_ptr = &Start;
        while (ptr != nullptr)
        {
          *local_ptr = new list_entry(ptr->Data);
          local_ptr = &(*local_ptr)->Next;
          ptr = ptr->Next;
        }
      } /* End of 'Clone' function */

    public:
      /* Operator = redefenition function.
       * ARGUMENTS:
       *   - list to copy:
       *       const list &NewList;
       * RETURNS:
       *   (list &) result list.
       */
      list & operator=( const list &NewList )
      {
        Clone(NewList);

        return *this;
      } /* End of 'operator=' function */
    }; /* End of 'list' class */

  /* Operator << redefenition function.
   * ARGUMENTS:
   *   - stream:
   *       std::ostream &stream;
   *   - list to print:
   *       list<Type> listy;
   * RETURNS:
   *   (std::ostream &) input stream.
   */
  template<typename Type>
    std::ostream & operator<<( std::ostream &stream, list<Type> &listy )
    {
      listy.Display(stream);

      return stream;
    } /* End of 'operator<<' function */
} /* end of 'dp1' namespace */

/* Main function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (int) exit code.
 */
int main( void )
{
  /*
  dp1::list<double> L;
  L.PushFront(30.47);
  L.PushBack(102.8);
  double x;
  if (L.PopBack(x))
    std::cout << "Deleted:" << x << std::endl;
  if (L.PopFront(x))
    std::cout << "Deleted:" << x << std::endl;
  L.PushFront(2).PushBack(30);
  L.Display();
  dp1::list<double> LL;
  LL = L;
  std::cout << LL;
  L.Clear();
  std::cout << "IsEmpty:" << L.IsEmpty() << std::endl;
  L.Display();
  */

  dp1::list<dp1::list<double>> Multi;
  dp1::list<double> tmp;

  tmp.PushBack(5);
  Multi.PushBack(tmp);
  tmp.PushBack(6);
  Multi.PushBack(tmp);
  tmp.PushBack(7);
  Multi.PushBack(tmp);

  std::cout << Multi;

  return 0;
} /* End of 'main' function */

/* END OF 'MAIN.CPP' FILE */

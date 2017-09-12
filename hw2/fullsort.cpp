#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <cstdlib>

using namespace std;


struct Node {
    int value;
    Node *next;
};

Node* breakpointHelper (Node* in)
{
  if (in -> next == NULL) // reached end of list, no breakpoint found
  {
    // returns NULL
 
    return NULL;

  }

  else // not end of list, look for breakpoint
  {
    // check if the next value is less than this onee
    if ((in -> value) > (in -> next -> value))
    {
      return in;
    }
    else // checks next location in the list for breakpoint
    {
      return breakpointHelper(in -> next);
    }
  }

  return NULL;
}

Node* endHelper (Node* in)
{
  if (in -> next == NULL) // reached end of list
  {

    //cout << "end of list is number " << in -> value << endl;
    return in;
  }

  return endHelper(in -> next);
}

Node* fullsort (Node* in)
{

  /*
  << "fullsort List" << endl;
  Node* printable = in;
  while (printable != NULL)
  {
    cout << printable -> value << " ";
    printable = printable -> next;

  }
  cout << endl;
  */



  // use recursion to find "breakpoint", where list is unsorted
  Node* breakpoint = breakpointHelper (in);

    if (breakpoint == NULL)
    {
      return in;
    }

  // use recursion to find the end of the list

  Node* end = endHelper (in);

  // make value after breakpoint NULL
  // save the lowest value as start

  Node* begining = breakpoint -> next;
  breakpoint -> next = NULL;

  // put the begining at the end

  end -> next = in;

  // return list starting from one after breakpoint (begining)

  return begining;
  
}
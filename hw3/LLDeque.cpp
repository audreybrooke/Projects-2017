#include "LLDeque.h"
#include <stddef.h>
#include <iostream>
#include <cstddef>

using namespace std;


  LLDeque :: LLDeque () // initializes an empty deque
  {
    head = NULL;
    tail = NULL;
    size = 0;

  }

  LLDeque :: ~LLDeque () // deallocates all dynamically allocated memory
  {

    for (int i = 0; i < size; ++i)
    {
      head = head -> next;
      delete head -> prev;
    }

  }

  void LLDeque :: pushback (char x) // append x at one end of the deque.
  {
    if (size == 0)
    {
      Node* add = new Node (x);
      head = add;
      tail = add;
      size ++;
    }

    else
    {
      Node* add = new Node (x, NULL, tail);
      tail -> next = add;
      tail = add;
      size ++;
    }

  }

  void LLDeque :: popback () /* remove at the same end of the deque.
                     Does nothing if called on an empty deque. */
  {
    if (size == 0)
    {
      return;
    }

    Node* temp = tail;
    tail = tail-> prev;
    delete temp;
    size--;

  }

  char LLDeque :: getback () /* returns the element at the same end of the deque.
                      Returns '\0' if called on an empty deque. */
  {
    if (size == 0)
    {
      return '\0';
    }

    return tail->data;

  }

  void LLDeque :: pushfront (char x) // "prepend" x at the other end of the queue.
  {
    if (size == 0)
    {
      Node* add = new Node (x);
      head = add;
      tail = add;
      size ++;
    }

    else
    {
      Node* add = new Node (x, head, NULL);
      head -> prev = add;
      head = add;
      size ++;
    }


  }

  void LLDeque :: popfront () /* remove at the other end of the deque.
                       Does nothing if called on an empty deque. */
  {
    if (size == 0)
    {
      return;
    }

    Node* temp = head;
    head = head-> next;
    delete temp;
    size--;
  }

  char LLDeque :: getfront() /* returns the element at the other end of the deque.
                      Returns `\0` if called on an empty deque. */
  {
    if (size == 0)
    {
      return '\0';
    }

    return head->data;
  }

  bool LLDeque :: isempty() // returns whether the deque is empty.
  {
    if (size > 0)
    {
      return false;
    }

    return true;

  }
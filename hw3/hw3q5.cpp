#include "LLDeque.h"
#include <stddef.h>
#include <iostream>
#include <cstddef>
#include <fstream>

using namespace std;

bool doesCancel (char first, char second);


int main(int argc, char const *argv[])
{
  // Variables

  LLDeque* person1Deque = new LLDeque ();
  LLDeque* person2Deque = new LLDeque ();
  LLDeque* helperDeque = new LLDeque ();
  int steps1 = 0;
  int steps2 = 0;


  // take in file
  if (argc < 2)
  {
    cerr << "No file given" << endl;
    return 0;
  }

  ifstream ifile(argv[1]);

  // check if file worked
  if (ifile.fail())
  {
    cerr << "Failed to read file" << endl;
    return 0;
  }





  // itterate through file
  // keep track of number of steps for person 1 and 2

  int person;
  char direction;
  ifile >> person;
  ifile >> direction;

  while (!ifile.fail())
  {
    if (!(direction == 'N' || direction == 'S' || direction == 'E' || direction == 'W'))
    {
      cerr << "Invalid direction" << endl;
    }
    if (person == 1)
    {
      // push front direction
      person1Deque -> pushback(direction);
      steps1++;
    }
    else if (person == 2)
    {
      // push back direction
      person2Deque -> pushback(direction);
      steps2++;
    }
    else
    {
      cerr << "Line must begin with a 1 or 2" << endl;
      return 0;
    }

    ifile >> person;
    ifile >> direction;
  }

  // itterate through deques
  // if there are 2 directions that cancel out ie. N,S in a row
  // remove both
  char direction1, direction2;

  while (!(person1Deque -> isempty()))
  {
    if (helperDeque -> isempty())
    {
      // helper deque is empty
      // nothing to compare the first element of person1deque with
      // put the first direction in person1deque in helper
      // so it can be compared with next direction
      helperDeque -> pushback((person1Deque -> getfront()));
      person1Deque -> popfront();
    }

    else
    {
      // helper deque not empty
      // compare the last direction in helper with first
      // element in person1deque

      direction1 = helperDeque -> getback();
      direction2 = person1Deque -> getfront();

      if (doesCancel(direction1, direction2))
      {
        // the directions cancel
        // the person retraced their steps and thus wound the
        // string back up, so these steps need not be
        // counted
        // remove them from the helper and person1 deques
        helperDeque -> popback();
        person1Deque -> popfront();
      }

      else
      {
        // directions did not cancel
        // safe to add the direction from person1 to helper deque

        helperDeque -> pushback(direction2);
        person1Deque -> popfront();

      }
    }
  }

    // move valus from helper back to person2Deque

  while (!(helperDeque -> isempty()))
  {
    person1Deque -> pushback(helperDeque -> getfront());
    helperDeque -> popfront();
  }




  // repeat cancelation process with person2deque

  while (!(person2Deque -> isempty()))
  {
    if (helperDeque -> isempty())
    {
      // helper deque is empty
      // nothing to compare the first element of person2deque with
      // put the first direction in person2deque in helper
      // so it can be compared with next direction
      helperDeque -> pushback((person2Deque -> getfront()));
      person2Deque -> popfront();
    }

    else
    {
      // helper deque not empty
      // compare the last direction in helper with first
      // element in person2deque

      direction1 = helperDeque -> getback();
      direction2 = person2Deque -> getfront();

      if (doesCancel(direction1, direction2))
      {
        // the directions cancel
        // the person retraced their steps and thus wound the
        // string back up, so these steps need not be
        // counted
        // remove them from the helper and person1 deques
        helperDeque -> popback();
        person2Deque -> popfront();
      }

      else
      {
        // directions did not cancel
        // safe to add the direction from person1 to helper deque

        helperDeque -> pushback(direction2);
        person2Deque -> popfront();

      }
    }
  }

  // move valus from helper back to person2Deque

  while (!(helperDeque -> isempty()))
  {
    person2Deque -> pushback(helperDeque -> getfront());
    helperDeque -> popfront();
  }




  // pop while the person1Deque and person2Deque have same direction
  // return addition of remaining steps
  int total = 0;

  while (!(person1Deque -> isempty()) && !(person2Deque -> isempty()))
  {
    if (person1Deque -> getfront() == person2Deque -> getfront())
    {
      person1Deque -> popfront();
      person2Deque -> popfront();
    }
    else
    {
      break;
    }
  }

  // count remaining steps in both deques

  while (!(person1Deque -> isempty()))
  {
    total++;
    person1Deque -> popfront();
  }

  while (!(person2Deque -> isempty()))
  {
    total++;
    person2Deque -> popfront();
  }

  // output the remaining space

  cout << total << endl;

  



 
  // delete the deques

  delete person1Deque;
  delete person2Deque;
  delete helperDeque;

  return 0;
}

bool doesCancel (char first, char second)
{
  if ((first == 'N') && (second == 'S'))
  {
    return true;
  }
  else if ((first == 'S') && (second == 'N'))
  {
    return true;
  }
  else if ((first == 'E') && (second == 'W'))
  {
    return true;
  }
  else if ((first == 'W') && (second == 'E'))
  {
    return true;
  }

  return false;
}
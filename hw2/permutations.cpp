#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <string>

using namespace std;

void helper (string in, int firstIndex)
{
  // checks if switching is finished and permutation is ready to print
  // doesn't need to switch because it would be switching the last char
  // with itself
  if (firstIndex == (int) in.length())
  {
    cout << in << endl;
  }

  else
  {

    // goes through the inputed string and switches the start letter
    // with all those after it then calls helper on each new string
    // starting one index down so the switching starts further
    // this encapsulates all permutations becuse the firstIndex
    // is always switched with itself to maintain that permutation

    for (int i = firstIndex; i < (int) in.length(); ++i)
    {
      // switch index first with i
      char temp = in[firstIndex];
      in[firstIndex] = in [i];
      in [i] = temp;
      // call to swap next index
      helper (in, firstIndex+1);

    }
  }

}

void permutations(std::string in)
{

  // needs helper becuase I can't write this without the int
  // to keep track of which indexes are switched

  helper (in, 0);
  return;
}
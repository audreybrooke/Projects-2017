#include "company.h"
#include <stddef.h>
#include <iostream>

using namespace std;

CompanyTracker::CompanyTracker (int n)
  // initializes the tracker with n students and their 1-person companies
{
  numCompanies = n;
  companies = new Company* [numCompanies];
  for (int i = 0; i < numCompanies; ++i)
      companies[i] = new Company ();
}

CompanyTracker::~CompanyTracker ()
  // deallocates all dynamically allocated memory
{
  // your implementation goes here

  // go through companies array and at each index find largest parent
  // delete that parent and continue until largest parent is itself
  // delete self and move to next index

  for (int i = 0; i < numCompanies; ++i)
  {
    Company* largestParent = largestCompany(i);
    while (largestParent != companies[i])
    {
      Company* toDelete = largestParent;
      toDelete -> merge1 -> parent = NULL;
      toDelete -> merge2 -> parent = NULL;
      delete toDelete;
      largestParent = largestCompany(i); 
    }

    delete companies [i];
  }

  delete [] companies;
}

void CompanyTracker::merge (int i, int j)
  /* Merges the largest companies containing students i and j,
     according to the rules described above.
     That is, it generates a new Company object which will
     become the parent company of the largest companies currently
     containing students i and j.
     If i and j already belong to the same company (or are the same),
     merge doesn't do anything.
     If either i or j are out of range, merge doesn't do anything. */
{
  // your implementation goes here

  // check if i or j are out of range
  if (i >= numCompanies || j >= numCompanies)
  {
    return;
  }


  // check if i and j are the same

  if (i == j)
  {
    return;
  }

  // find the largest parent of i

  Company* iLargest = largestCompany (i);

  // find the largest parent of j

  Company* jLargest = largestCompany(j);

  // check if i and j belong to the same company

  if (jLargest == iLargest)
  {
    return;
  }

  // make new company object that is the parent of
  // the2 compainies found previously

  Company* newParent = new Company (iLargest, jLargest);

  // set the parent of these to be the new object

  iLargest -> parent = newParent;
  jLargest -> parent = newParent;


}

void CompanyTracker::split (int i)
  /* Splits the largest company that student i belongs to,
     according to the rules described above.
     That is, it deletes that Company object, and makes sure that
     the two subcompanies have no parent afterwards.
     If i's largest company is a 1-person company, split doesn't do anything.
     If i is out of range, split doesn't do anything. */
{
  // your implementation goes here

  // check if i is in range

  if (i >= numCompanies)
  {
    return;
  }

  // check if i does not have a parent

  if (companies[i] -> parent == NULL)
  {
    return;
  }

  // find largest company that i belongs to

  Company* iLargest = largestCompany(i);

  // save the 2 children

  Company* child1 = iLargest -> merge1;
  Company* child2 = iLargest -> merge2;

  // delete the parent

  delete iLargest;

  // make childrens' parent nullptr

  child1 -> parent = NULL;
  child2 -> parent = NULL;
  
}

bool CompanyTracker::inSameCompany (int i, int j)
  /* Returns whether students i and j are currently in the same company.
     Returns true if i==j.
     Returns false if i or j (or both) is out of range. */
{
  // your implementation goes here

  // if i == j return true

  if (i == j)
  {
    return true;
  }

  // if i or j are out of range return false

  if (i >= numCompanies || j >= numCompanies)
  {
    return false;
  }

  // find i and j's largest parent

  Company* iLargest = largestCompany (i);
  Company* jLargest = largestCompany (j);

  // check if they are the same

  if (iLargest == jLargest)
  {
    return true;
  }

  return false;
}

Company* CompanyTracker:: largestCompany (int i)
{
  // returns largest company that i is a part of
  // find the largest parent of i by looking at the parent then
  // checking if null, if not look a next parent, etc.

  Company* initalCompany = companies[i];
  Company* nextParent = initalCompany;

  while (nextParent -> parent != NULL)
  {
    nextParent = nextParent -> parent;
  }

  return nextParent;

}
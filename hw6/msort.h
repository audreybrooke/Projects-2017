#ifndef MSORT_H
#define MSORT_H

#include "functor.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;
 
template <class T, class Comparator>
  void merge (vector<T>& myArray, int k, int l,
    int r, vector<int> indices, Comparator comp)
  {
  	// cout << "entered merge " << indices.size()/2 << endl;

  	vector<T> temp;

  	int smallestIndex = 0;
  	// int nsmv = 0;

  	// iterate through all spots in total section being merged
  	for (int j = 0; j < r-l+1; j++)
  	{

  		// find smallest value of all k sections
  		for (int i = 0; i < (int) indices.size(); i+=2)
  		{

  			// cout << ", comparing " << myArray[indices[i]] << " and " << myArray[indices[smallestIndex]] << endl;

  			if (indices[i] <= indices[i+1] &&
  				comp (myArray[indices[i]], myArray[indices[smallestIndex]]))
  			{
  				// cout << "!! " << myArray[indices[i]] << " is less than " << myArray[indices[smallestIndex]] << endl;  				
  				smallestIndex = i;
  			}
  			// else if (indices[i] <= indices[i+1]) nsmv = i;
  		}

  		// put smallest element in temp array
  		cout << "smallest index is " << smallestIndex << endl;
  		temp.push_back(myArray[indices[smallestIndex]]);
  		// cout << "* push back " << myArray[indices[smallestIndex]] << " successfull" << endl;

  		// increment this index to show that this value has been added
  		indices[smallestIndex]++;
  		// cout << "indices incremented" << endl;
  			for (int i = 0; i < (int) indices.size(); ++i)
  			{
  				// cout << indices[i]<<endl;
  			}

  		// update smallestindex
  		for (int s = 0; s < (int)indices.size(); s+=2)
  		{
  			if (indices[s] <= indices[s+1])
  			{
  				smallestIndex = s;
  				cout << "starter smallestIndex is " << s << endl;
  				break;
  			}
  		}
  		
  	}

  	// move sorted section into actual array
  	// // cout << "begining copying" << endl;
  	cout << "temp is: ";
  	for (int i = 0; i < (int)temp.size(); ++i)
  	{
  		myArray[i+l] = temp[i];
  		cout << temp[i] <<", ";
  	}
  	cout << endl;

  	// // cout << "exiting merge" << endl << endl << endl << endl;
  	//// cout << myArray[0]<<myArray[1]<<endl;

  }



 template <class T, class Comparator>
  void mSort (vector<T>& myArray, int k, int l, int r, Comparator comp)
  {

  	cout << "l = " << l << " r = " << r <<  " k = " << k << endl;

  	// cout << "entering mSort function" << endl;
  	if (l < r && (r-l+1 < k))
  	{
  		// cout << "r-l (elements to be sorted) is less than k" << endl;
  		// there are fewer elements than desired sections remaining
  		// put each element in its own section
  		vector<int> arrOfIndices;
  		for (int i = 0; i < r-l + 1; i++)
  		{
  			arrOfIndices.push_back(i+l);
  			arrOfIndices.push_back(i+l);  			
  		}
  		// mSort (myArray, r-l, l, r, comp);
  		// cout << "calling merge. arrOfIndices is:" << endl;
  			for (int i = 0; i < (int)arrOfIndices.size(); ++i)
  			{
  				// cout << arrOfIndices[i] << endl;
  			}
  			// cout << "r-l+1 is " << r-l+1 << endl;

  		merge (myArray, r-l+1, l, r, arrOfIndices, comp);
  	}

  	else if (l<r)
  	{
  		// cout << "r-l not less than k, but l < r" << endl;

  		vector<int> arrOfIndices;

  		// determine the cut off points for each merge section
  		int prev = l-1;
  		for (int i = 0; i < k-1; i++)
  		{
  			arrOfIndices.push_back(min(r,prev+1));
  			arrOfIndices.push_back(min(r, prev+((r-l+1)/k)));
  			prev = prev+((r-l+1)/k);
  		}
  		arrOfIndices.push_back(min(r, prev+1));
  		arrOfIndices.push_back(r);

  		// call merge recursively on k subsets of this portion of the array
  		for (int i = 0; i < (int) arrOfIndices.size(); i+=2)
  		{
  			mSort(myArray, k, arrOfIndices[i], arrOfIndices[i+1], comp);
  		}

  		cout << "calling merge. arrOfIndices is:" << endl;
  			for (int i = 0; i < (int)arrOfIndices.size(); ++i)
  			{
  				cout << arrOfIndices[i] << endl;
  			}
  	 	
  	 	merge(myArray, k, l, r, arrOfIndices, comp);
  	 }
  }

   template <class T, class Comparator>
  void mergeSort (std::vector<T>& myArray, int k, Comparator comp)
  {
  	// divide the array into k equal parts, sort each part,
  	// and then run a k-way merge function

  	mSort(myArray, k, 0, myArray.size() - 1, comp);

  	
  }
  
#endif

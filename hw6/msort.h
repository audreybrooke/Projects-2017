#ifndef MSORT_H
#define MSORT_H

#include "functor.h"
#include <string>
#include <vector>


 
template <class T, class Comparator>
  void merge (vector<T>& myArray, int k, int l, int r, vector<int>& indices, Comparator comp)
  {
  	vector<T> temp;

  	// iterate through all spots in total section being merged
  	for (int j = 0; j < l-r; j++)
  	{
  		int smallestIndex = 0;
  		// int smallestValue = myArray[0];

  		// find smallest value of all k sections
  		for (int i = 0; i < 2*k; i+=2)
  		{
  			if (indices[i] <= indices[i+1] &&
  				comp (myArray[indices[i]], myArray[indices[smallestIndex]]))
  			{
  				smallestIndex = i;
  			}
  		}

  		// put smallest element in temp array
  		temp.push_back(myArray[indices[smallestIndex]]);

  		// increment this index to show that this value has been added
  		indices[smallestIndex]++;
  	}

  	// move sorted section into actual array
  	for (int i = 0; i < r+1-l; ++i)
  	{
  		myArray[i+1] = temp[i];
  	}

  }



 template <class T, class Comparator>
  void mSort (vector<T>& myArray, int k, int l, int r, Comparator comp)
  {
  	if (l-r < k)
  	{
  		// there are fewer elements than desired sections remaining
  		// put each element in its own section
  		vector<int> arrOfIndices;
  		for (int i = 0; i < l-r; i++)
  		{
  			arrOfIndices.push_back(i);
  			arrOfIndices.push_back(i);  			
  		}
  		// mSort (myArray, l-r, l, r, comp);
  		merge (myArray, l-r, l, r, arrOfIndices, comp);
  	}

  	else if (l<r)
  	{
  		vector<int> arrOfIndices;

  		// determine the cut off points for each merge section
  		int prev = l-1;
  		for (int i = 0; i < k; i++)
  		{
  			arrOfIndices.push_back(min(r,prev+1));
  			arrOfIndices.push_back(min(r, prev+((r-l)/k)));
  		}

  		// call merge recursively on k subsets of this portion of the array
  		for (int i = 0; i < 2*k; i+=2)
  		{
  			mSort(myArray, k, arrOfIndices[i], arrOfIndices[i+1], comp);
  		}
  	 	
  	 	merge(myArray, k, l, r, arrOfIndices, comp);
  	 }
  }

   template <class T, class Comparator>
  void mergeSort (std::vector<T>& myArray, int k, Comparator comp)
  {
  	// divide the array into k equal parts, sort each part,
  	// and then run a k-way merge function

  	mSort(myArray, k, 0, rmyArray.size() - 1);

  	
  }
  
#endif

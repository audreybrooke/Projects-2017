#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Please provide an input and output file." << endl;
    return 1;
  }
  ifstream input(argv[1]);
  ofstream output(argv[2]);

  if (input.fail() || output.fail())
  {
  	cerr << "Invalid file name" << endl;
  	return 1;
  }

  int experiments;
  int numsubjects;
  string **history;
  string line;
  string curr;

  //for each experiment, you will need to keep track of the number
  //of subjects; and for each subject, of their history

  bool firstCommand = true;


  //loop to read The Rani's logbook.
  while(getline(input, curr)) {
  	line = curr;


  	// count the number of parameters in each line

  	stringstream cc;
  	cc << curr;
  	string dummy;
  	int numParameters = 0;
  	while (cc >> dummy) 
  	{
  		numParameters++;
  	}

	  stringstream ss;
	  ss << curr;
	  ss >> curr;


  // check if first command is START
	  if (firstCommand)
	  {
	  	if (curr != "START")
	  	{
	  		output << "Error - no subjects yet" << endl;
	  		continue;
	  	}

	  	else
	  	{
	  		firstCommand = false;
	  	}
	  }



	  if (curr == "START") {
	    // Hint: This does not cover all errors yet.


	    // delete old history array if this is not the first call to start

	    if (numsubjects != 0 || experiments != 0)
	    {
	    	for (int i = 0; i < experiments; ++i)
	    	{
	    		delete [] history [i];
	    	}

	    	delete [] history;
	    }

	    if (numParameters < 2)
	    {
	    	output << "Error - incorrect command: " << line << endl;
  		    output << "Too few parameters" << endl;
  		    continue;
	    }

		  int n;
		  double t, dn;
		  ss >> t;

		  if (ss.fail()) {
		    output << "Error - incorrect command: " << line << endl;
  		    output << "Parameter should be an integer" << endl;
  		    continue;
		  }
		  
		  double remainder = modf (t, &dn);
		  n = (int) dn;

		  if (remainder != 0)
		  {
		  	output << "Error - incorrect command: " << line << endl;
  		    output << "Parameters should be an integer" << endl;
  		    continue;
		  }

		  else if (n < 0) {
		    output << "Error - incorrect command: " << line << endl;
		    output << "Number out of range" << endl;
		    continue;
		  }
		  else {

		  	// starts a new set of experiments with n subjects
		  	// all n subjects added to experiment 0

		  	// do I need to dealocate memory in history before
		  	// begining?

		  	numsubjects = n;
		  	experiments = 1;

		  	// creates 2d array with one row
		  	history = new string*[1];

		  	// creats row with n elements (cols)
		  	history[0]= new string[n];


			// sets the first experiment to 0 for all mice
		  	for (int i = 0; i < n; ++i)
		  	{
		  		history[0][i] = "0";
		  	}

		  }
	  }
	  else if (curr == "ADD") {

	  	// Adds a new experiment, which recieves the next
	  	// highest number
	  	// Remember that experiement 0 is the pool

	  	experiments++;

	  	// create new 2d array with extra row
	  	// copy data over
	  	// delete old array

	  	string **newArray;
	  	newArray = new string* [experiments];

	  	// create an array with extra row
	  	for (int i = 0; i < experiments; ++i)
	  	{
	  		newArray[i]= new string [numsubjects];
	  	}

	  	// coppies data from "old" history to newArray
	  	for (int r = 0; r < experiments-1; ++r)
	  	{
	  		for (int c = 0; c < numsubjects; ++c)
	  		{
	  			newArray[r][c] = history[r][c];
	  		}
	  	}


	  	// delete memory allocation of history

	  	for (int i = 0; i < experiments-1; ++i)
	  	{
	  		delete [] history[i];
	  	}

	  	delete [] history;


	  	// reallocate memory for history

	  	history = new string* [experiments];

	  	for (int i = 0; i < experiments; ++i)
	  	{
	  		history[i] = new string [numsubjects];
	  	}

	  	// move elements from newArray to history

	  	for (int r = 0; r < experiments; ++r)
	  	{
	  		for (int c = 0; c < numsubjects; ++c)
	  		{
	  			history[r][c] = newArray[r][c];
	  		}
	  	}

	  	// deallocate memory from neWArray

	  	for (int i = 0; i < experiments; ++i)
	  	{
	  		delete [] newArray[i];
	  	}

	  	delete [] newArray;


	  }
	  else if (curr == "MOVE") {

	  	if (numParameters < 5)
	  	{
	  		output << "Error - incorrect command: " << line << endl;
  		    output << "Too few parameters" << endl;
  		    continue;
	  	}

	  	// read in x,y,n,m
	  	// moves subjects nn to m from eperiment x to experiment y
	  	// shift down subjects with numbers higher than y
	  	// they now start being numbered at nn
	  	// add new location to the string



	  	int x, y, n, m;
	  	double dx, dy, dn, dm, ix, iy, in, im;
	  	ss >> dx >> dy >> dn >> dm;

	  	if (ss.fail()) {
		    output << "Error - incorrect command: " << line << endl;
  		    output << "Parameters should be 4 integers" << endl;
  		    continue;
		}

		double xremainder = modf (dx, &ix);
		double yremainder = modf (dy, &iy);
		double nremainder = modf (dn, &in);
		double mremainder = modf (dm, &im);
		x = (int) ix;
		y = (int) iy;
		n = (int) in;
		m = (int) im;

		  if (xremainder != 0 || yremainder != 0 || nremainder !=0 || mremainder != 0)
		  {
		  	output << "Error - incorrect command: " << line << endl;
  		    output << "Parameters should be 4 integers" << endl;
  		    continue;
		  }

		else if (x < 0 || y < 0 || n < 0 || m < 0)
		{
			output << "Error - incorrect command: " << line << endl;
  		    output << "Number out of range" << endl;
  		    continue;
		}
		else if (n >= numsubjects || m >= numsubjects || x >= experiments || y >= experiments)
		{
			output << "Error - incorrect command: " << line << endl;
  		    output << "Number out of range" << endl;
  		    continue;
		}
		else if (n > m)
		{
			output << "Error - incorrect command: " << line << endl;
  		    output << "Invalid range of subjects to move" << endl;
  		    continue;
		}

		// finds the last index filled in experiment y
		int openSpot = 0;

		for (int i = 0; i < numsubjects; ++i)
		{
			if (history[y][i] == "")
			{
				openSpot = i;
				break;
			}
		}

		// takes items n-m in experiment x and moves them to y 
		for (int i = n; i <= m; ++i, ++openSpot)
		{
			history[y][openSpot] = history[x][i];
			history[y][openSpot] += '0'+y;
			history[x][i] = "";
		}

		// moves remaining mice down in list
		//

		for (int i = m+1, j = n; i < numsubjects; ++i, ++j)
		 {
		 	history[x][j] = history[x][i];
		 	history[x][i] = "";
		 } 


	  }
	  else if (curr == "QUERY") {

	  	if (numParameters < 3)
	  	{
	  		output << "Error - incorrect command: " << line << endl;
  		    output << "Too few parameters" << endl;
  		    continue;
	  	}

	  	// read in ex,index
	  	// returns the sequence of experiments that the
	  	// index-th subject
	  	// in experiment ex was exposed to in order
	  	// don't output the subject pool, 0

	  	int ex, index;
	  	double dex, dindex, iex, iindex;
	  	ss >> dex >> dindex;

	  	if (ss.fail()) {
		    output << "Error - incorrect command: " << line << endl;
  		    output << "Parameters should be 2 integers" << endl;
  		    continue;
		}

		double dexremainder = modf (dex, &iex);
		double dindexremainder = modf (dindex, &iindex);

		ex = (int) iex;
		index = (int) iindex;

		if (dexremainder != 0 || dindexremainder != 0)
		{
		    output << "Error - incorrect command: " << line << endl;
  		    output << "Parameters should be 2 integers" << endl;
  		    continue;
 		}

		else if (index < 0 || index >= numsubjects || ex < 0 || ex >= experiments)
		{
			output << "Error - incorrect command: " << line << endl;
  		    output << "Input out of range" << endl;
  		    continue;
		}


		// prints the experiment history of mice index in
		// experiment ex

		string theHistory = history[ex][index];
		for (int i = 0; i < theHistory.length(); ++i)
		{
			if (theHistory[i] != '0')
				output << theHistory[i] << " ";
		}
		output << endl;


	  }
	  else {

	  	// error statement - wrong command

		output << "Error - incorrect command: " << line << endl;
	  	output << "Command does not exist" << endl;
		  
	  }
  }

  // while loop is over, deallocate all memory

  for (int i = 0; i < experiments; ++i)
  {
  	delete [] history[i];
  }
  delete [] history;

  return 0;
}

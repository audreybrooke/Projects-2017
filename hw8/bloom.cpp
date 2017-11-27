#include "bloom.h"
#include <string>
#include <iostream>

using namespace std;


int main(int argc, char const *argv[])
{
	BloomFilter* bf = new BloomFilter(50);

	bf->insert("https://www.usc.edu/cs_rules");
	bf->insert("https://www.usc.edu/cs_ruled");
	bf->insert("https://www.usc.edu/cs_rule");
	bf->insert("https://www.usc.edu/cs_rule");
	bf->insert("https://www.usc.edu/cs_rule");
	bf->insert("https://www.usc.edu/cs_rule");
	bf->insert("https://www.usc.edu/cs_rule");
	bf->insert("https://www.usc.edu/cs_rule");
	bf->insert("https://www.usc.edu/cs_rule");
	bf->insert("https://www.usc.edu/cs_rulep");
	bf->insert("https://www.usc.edu/cs_ruleo");
	bf->insert("https://www.usc.edu/cs_rulek");
	bf->insert("https://www.usc.edu/cs_rulezz");

	cout << bf->contains("https://www.usc.edu/cs_rules") << endl;	// 1
	cout << bf->contains("https://www.usc.edu/cs_ruled") << endl;	// 1
	cout << bf->contains("https://www.usc.edu/cs_rule") << endl;	// 1
	cout << bf->contains("https://www.usc.edu/cs_rulep") << endl;	// 1
	cout << bf->contains("https://www.usc.edu/cs_rulq") << endl;	// 0?
	cout << bf->contains("https://www.usc.edu/cs_rulw") << endl;	// 0?
	cout << bf->contains("https://www.usc.edu/cs_rull") << endl;	// 0?
	cout << bf->contains("https://www.usc.edu/cs_rulo") << endl;	// 0?
	cout << bf->contains("https://www.usc.edu/cs_rula") << endl;	// 0?
	cout << bf->contains("https://www.usc.edu/cs_rulz") << endl;	// 0?
	cout << bf->contains("https://www.usc.edu/cs_rulse") << endl;	// 0?
	cout << bf->contains("https://www.usc.edu/cs_rulez") << endl;	// 0?
	cout << bf->contains("https://www.usc.edu/cs_rulde") << endl;	// 0?
	cout << bf->contains("https://www.usc.edu/cs_rulel") << endl;	// 0?



	delete bf;

	return 0;
}

/*
* Add this string to the Bloom Filter.
* Do nothing if the string is already in the Bloom Filter.
 */
void BloomFilter::insert (string input)
{
	int h1 = hash1(input);
	int h2 = hash2(input);
	int h3 = hash3(input);

	bloom[h1] = true;
	bloom[h2] = true;
	bloom[h3] = true;
}
   
/* returns whether this string is in the set.
* Being a Bloom Filter, may sometimes return "yes" when the true answer
* is "no". 
*/ 
bool BloomFilter::contains (string input)
{
	int h1 = hash1(input);
	int h2 = hash2(input);
	int h3 = hash3(input);

	if (bloom[h1] && bloom[h2] && bloom[h3])
	{
		return true;
	}

	return false;
}


BloomFilter::BloomFilter(unsigned int size)
{
	if (size <= 11) capacity = 11;
	else if (size <= 23) capacity = 23;
	else if (size <= 47) capacity = 47;
	else if (size <= 97) capacity = 97;
	else if (size <= 197) capacity = 197;
	else if (size <= 397) capacity = 397;
	else if (size <= 797) capacity = 797;
	else if (size <= 1597) capacity = 1597;
	else if (size <= 3203) capacity = 3203;
	else if (size <= 6421) capacity = 6421;
	else if (size <= 12853) capacity = 12853;
	else if (size <= 25717) capacity = 25717;
	else capacity = 51437;

	bloom = new bool[capacity];

}

BloomFilter::~BloomFilter()
{
	delete [] bloom;
}

int BloomFilter::hash1 (string input) const
{
	int r[21] = {50161, 22696, 273, 19159, 14692, 8255, 20154, 
		13109, 11098, 866, 15643, 11554, 38297, 42447, 9827, 
		9648, 45568, 47227, 48459, 30713, 9110};

	int* w = new int[21];

	setW(w, input);

	long total;

	for (int i = 0; i < 21; ++i)
	{
		total += ((long)r[i] * (long)w[i]) % capacity;
	}

	delete [] w;

	return total % capacity;

}



int BloomFilter::hash2 (string input) const
{
	int p = determineP ();

	int r[21] = {50161, 22696, 273, 19159, 14692, 8255, 20154, 
		13109, 11098, 866, 15643, 11554, 38297, 42447, 9827, 
		9648, 45568, 47227, 48459, 30713, 9110};

	int* w = new int[21];

	setW(w, input);


	long total;

	for (int i = 0; i < 21; ++i)
	{
		total += ((long)r[i] * (long)w[i]) % p;
	}

	delete [] w;

	return p - (total % p);
}

int BloomFilter::hash3 (string input) const
{
	int* w = new int[21];
	setW(w, input);

	long total;

	for (int i = 0; i < 21; ++i)
	{
		total += ((long)w[i]) % capacity;
	}

	delete [] w;

	return total % capacity;
}


int BloomFilter::determineValue(char i) const
{
	int value = 0;
	if (i == '.') value = 1;
	else if (i == '/') value = 2;
	else if (i == ':') value = 3;
	else if (i == '_') value = 4;
	else value = (i - 'a') + 5;

	return value;
}

int BloomFilter::determineP() const
{
	if (capacity <= 11) return 7;
	else if (capacity <= 23) return 19;
	else if (capacity <= 47) return 43;
	else if (capacity <= 97) return 89;
	else if (capacity <= 197) return 193;
	else if (capacity <= 397) return 389;
	else if (capacity <= 797) return 787;
	else if (capacity <= 1597) return 1583;
	else if (capacity <= 3203) return 3191;
	else if (capacity <= 6421) return 6397;
	else if (capacity <= 12853) return 21841;
	else if (capacity <= 25717) return 25703;
	else return 51431;
}

void BloomFilter::setW(int* &w, string input) const
{

	int charValues[63] = 
	   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	int j, i;
	for (j = 0, i = 63 - (int) input.size(); i < 63; ++i, ++j)
	{
		charValues[i] = determineValue(input[j]);
	}

	for (j = 0, i = 0; i < 21; i++, j+=3)
	{
		w[i] = (31*31) * charValues[j] + 31 * charValues[j+1] + charValues[j+2];
	}

	/*cout << endl << "W values for " << input << endl;

	for (int i = 0; i < 21; ++i)
	{
		cout << "w[" << i << "]  =  " << w[i] << endl;
	}
	*/
}
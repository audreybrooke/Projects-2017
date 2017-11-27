#include <string>

class BloomFilter {
  public:

  BloomFilter (unsigned int size = 11);
  /* Constructor for the given 
  size (see below).*/
  ~BloomFilter();

  void insert (std::string input);
   /* Add this string to the Bloom Filter.
      Do nothing if the string is already in the Bloom Filter. */

  bool contains (std::string input);
  /* returns whether this string is in the set.
     Being a Bloom Filter, may sometimes return "yes" when the true
      answer is "no". */ 

  protected:
  int hash1 (std::string input) const;
  int hash2 (std::string input) const;
  int hash3 (std::string input) const;

  private:
  int determineValue (char i) const;
  int determineP () const;
  void setW(int* &w, std::string input) const;
  bool* bloom;
  unsigned int capacity;
};
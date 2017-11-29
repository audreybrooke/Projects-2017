#include <string>

struct TrieNode {
  bool inSet;   // we're not storing a value.
  TrieNode *parent;
  TrieNode *children[30];
};

class TrieSet {
 public:
  TrieSet();
  ~TrieSet();

  void insert (std::string input);
   /* Add this string to the set.
      Do nothing if the string is already in the set. */

  void remove (std::string input);
   /* Remove this string from the set.
      Do nothing if the string is not in the set. */

  bool contains (std::string input); // returns whether this string is in the set.
 
 private:
	TrieNode* root;
	int findIndex(char i);
	void destruct_helper(TrieNode* loc);
  void removeHelper(TrieNode* loc, std::string input);
};
#include <iostream>

class LineNumber {
  // abstract class for a BASIC Command

 public:
  LineNumber (int num);
  ~LineNumber();
  
  void print (std::ostream & o) const;
  // pure virtual print function. Don't implement!

private:
  int line;
};

// add below other classes that are needed
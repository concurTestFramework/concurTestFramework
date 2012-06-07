// Utility functions for scheduler.

#include <string>
#include <sstream>
using namespace std;



// Prototypes
extern "C" string boolToStr(const bool val);
extern "C" string intToStr(int num);
extern "C" void stoupper(std::string& s);



/*
 *  Returns integer to string
 */
extern "C" string intToStr(int num) {
  stringstream numAsAlpha;
  numAsAlpha << num;
  return numAsAlpha.str();
}


/*
 *  Returns string s in all capital letters.
 */
extern "C" void stoupper(std::string& s) {
  std::string::iterator i = s.begin();
  std::string::iterator end = s.end();

  while (i != end) {
    *i = std::toupper((unsigned char)*i);
    ++i;
  }
}

/*
 * Converts bool to string.
 */
extern "C" string boolToStr(const bool b) {
    ostringstream ss;
    ss << boolalpha << b;
    return ss.str();
}


#include "function.hpp"

int main() {
  string str = "";
  int result = 0;

  getline(cin, str);

  result = countVowels(str);

  cout << result << endl;

  return 0;
}

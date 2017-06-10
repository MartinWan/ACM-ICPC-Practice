#include <iostream>
#include <list>
using namespace std;

/**
  * Problem: https://open.kattis.com/problems/backspace
**/


int main() {
  string text;
  cin >> text;

  list<char> result;
  int n = text.length();
  int skips = 0;
  
  for (int i = n - 1; i >= 0; i--) {
    char c = text.at(i);
    if (c == '<') {
      skips++;
    } else { // character
      if (skips != 0) {
        skips--;
      } else {
        result.push_front(c);
      }
    }
  }

  list<char>::iterator i;
  for (i = result.begin(); i != result.end(); i++) {
    cout << *i;
  }

  cout << endl;

}

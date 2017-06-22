#include <stdio.h>
#include <iostream>
#include <map>
using namespace std;

int main() {
  int cases;
  scanf("%d", &cases);

  for (int i = 0; i < cases; i++) {
    int n;
    scanf("%d", &n);

    map<string, int> categories;
    for (int j = 0; j < n; j++) {
      string name;
      string category;
      cin >> name;
      cin >> category;
      
      categories[category] += 1;
    }
    int sum = 1;
    map<string, int>::iterator it = categories.begin();
    while (it != categories.end()) {
      sum *= it->second + 1;   
      
      ++it;
    }
    cout << sum - 1 << endl;
  }
}

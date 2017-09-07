#include <vector>
#include<algorithm>
#include <stdexcept>
#include <stdio.h>
#include <stack>
#include <stdlib.h>
#include <list>
#include <limits.h>
#include <math.h>
using namespace std;

struct point {
  int x, y;
  bool operator<(point& p0) {
    if (y == p0.y)
      return x < p0.x;
    return y < p0.y;
  }
};

// A utility function to find next to top in a stack
point nextToTop(stack<point> &S) {
  point p = S.top();
  S.pop();
  point res = S.top();
  S.push(p);
  return res;
}

// A utility function to return square of distance
// between p1 and p2
int distSq(point p1, point p2) {
  return (p1.x - p2.x)*(p1.x - p2.x) +
    (p1.y - p2.y)*(p1.y - p2.y);
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(point p, point q, point r) {
  int val = (q.y - p.y) * (r.x - q.x) -
    (q.x - p.x) * (r.y - q.y);

  if (val == 0) return 0;  // colinear
  return (val > 0)? 1: 2; // clock or counterclock wise
}

/*
 * Returns true iff the polar angle of p0->p1
 * is less than the polar angle of p0->p2.
 * Note** MUST set p0 before calling this compare function.
 */
point p0;
bool ascending_polar_angle(point& p1, point& p2) {
  int o = orientation(p0, p1, p2);
  int r; 
  
  if (o == 0) { // ties broken by smaller distance from origin
    return distSq(p0, p2) >= distSq(p0, p1);
  }
  return o == 2;
}


/*
 * Returns the convex hull of the points given in O(nlogn)
 * Throws logic_error if points do not contain at least 3
 * non-colinear points. 
 * Implementation based off of GeeksForGeeks post http://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/
 */
list<point> convex_hull(vector<point> points) {
  int n = points.size();  

  // swap points[0] with point with lowest y-coordinate
  int ymin = points[0].y, min = 0;
  for (int i = 1; i < n; i++) {
    if (points[i] < points[min])  
      ymin = points[i].y, min = i;
  }
  swap(points[0], points[min]);

  p0 = points[0];
  sort(points.begin()+1, points.end(), ascending_polar_angle);

  // If two or more points make same angle with p0,
  // Remove all but the one that is farthest from p0
  int m = 1; // size of convex hull
  for (int i=1; i<n; i++) {
    while (i < n-1 && orientation(p0, points[i], points[i+1]) == 0)
      i++;

    points[m] = points[i];
    m++;  
  }

  if (m < 3) {
	  throw logic_error("convex hull requires at least 3 non colinear-points");  
  }

  // Create an empty stack and push first three points
  stack<point> S;
  S.push(points[0]);
  S.push(points[1]);
  S.push(points[2]);

  // Process remaining n-3 points
  for (int i = 3; i < m; i++) {
    // Keep removing top while the angle formed by
    // points next-to-top, top, and points[i] makes
    // a non-left turn
    while (orientation(nextToTop(S), S.top(), points[i]) != 2)
      S.pop();
    S.push(points[i]);
  }

  // convert result
  list<point> result;
  while (!S.empty()) {
    result.push_back(S.top());
    S.pop();
  }

  return result;
}

int main() {
  int C;
  scanf("%d", &C);
  
  vector<point> points(C);
  
  int x, y;
  for (int i = 0; i < C; i++) {
    scanf("%d", &x);
    scanf("%d", &y);
    point p;
    p.x = x;
    p.y = y;
    points[i] = p;
  }
  list<point> hull;
  if (C < 3) {
    for (int i = 0; i < C; i++)
      hull.push_back(points[i]);
  } else {
    try {
      hull = convex_hull(points);
    } catch (logic_error& e) {
      for (int i = 0; i < C; i++) {
        hull.push_back(points[i]);
      }
    }
  };
  
  int maxDistSq = INT_MIN;
  for (list<point>::iterator i = hull.begin(); i != hull.end(); i++) {
    for (list<point>::iterator j = hull.begin(); j != hull.end(); j++) {
      maxDistSq = max(maxDistSq, distSq(*i, *j));
    }
  }
  printf("%.7f\n", sqrt(maxDistSq));

}

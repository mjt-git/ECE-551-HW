#include "circle.h"

#include <math.h>

#include <algorithm>
#include <cmath>
#define _USE_MATH_DEFINES

Circle::Circle(Point p, double r) : center(p), radius(r) {
}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double d = center.distanceFrom(otherCircle.center);
  double r2 = otherCircle.radius;
  if (radius == 0 || r2 == 0) {
    return 0;
  }
  else if (abs(radius - r2) >= d) {
    return std::min(radius, otherCircle.radius) * std::min(radius, otherCircle.radius) *
           M_PI;
  }
  else if (d >= (radius + otherCircle.radius)) {
    return 0;
  }
  else {  // d < radius
    double d1 = (radius * radius - r2 * r2 + d * d) / (2 * d);
    double d2 = d - d1;
    double theta1 = fmod(acos(d1 / radius) + 2 * M_PI, M_PI);
    double theta2 = fmod(acos(d2 / r2) + 2 * M_PI, M_PI);
    double sectorArea1 = radius * radius * theta1;
    double sectorArea2 = r2 * r2 * theta2;
    double triangleArea1 = radius * d1 * sin(theta1);
    double triangleArea2 = r2 * d2 * sin(theta2);
    /*if (d < x) {
      return sectorArea1 + r2 * r2 * M_PI - sectorArea2 - triangleArea1 + triangleArea2;
    }  */
    return sectorArea1 + sectorArea2 - triangleArea1 - triangleArea2;
  }
}

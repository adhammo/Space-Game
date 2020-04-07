#include "point.h"

FPoint::FPoint(const Point& point) : x(double(point.x)), y(double(point.y)) {}
Point::Point(const FPoint& point) : x(long(point.x)), y(long(point.y)) {}

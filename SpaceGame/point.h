#ifndef POINT_H
#define POINT_H

struct Point;
struct FPoint;

struct Point
{
	Point(const FPoint& point);
	Point(long _x, long _y) :x(_x), y(_y) {}
	long x;
	long y;
};

struct FPoint
{
	FPoint(const Point& point);
	FPoint(double _x, double _y) :x(_x), y(_y) {}
	double x;
	double y;
};

#endif //POINT_H
#include "geometry.hpp"

#include <vector>

geo::Angle2::Angle2(float x_rot, float y_rot) {
    this->x_rot = x_rot;
    this->y_rot = y_rot;
}

geo::Point2d::Point2d(float x, float y) {
    this->x = x;
    this->y = y;
}

geo::Point3d::Point3d(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

geo::Polygon2d::Polygon2d(std::vector<Point2d> points) {
    this->points = points;
}

geo::Polygon3d::Polygon3d(std::vector<Point3d> points) {
    this->points = points;
}

geo::Polygon2d::Polygon2d() {
    points = std::vector<Point2d>();
}

geo::Polygon3d::Polygon3d() {
    points = std::vector<Point3d>();
}

geo::Triangle2d::Triangle2d(Point2d point1, Point2d point2, Point2d point3) {
    points.push_back(point1);
    points.push_back(point2);
    points.push_back(point3);
}

geo::Triangle3d::Triangle3d(Point3d point1, Point3d point2, Point3d point3) {
    points.push_back(point1);
    points.push_back(point2);
    points.push_back(point3);
}

geo::Polyhedron3d::Polyhedron3d(std::vector<Triangle3d> faces) {
    this->faces = faces;
}

geo::Polyhedron3d::Polyhedron3d() {
    this->faces = std::vector<geo::Triangle3d>();
}

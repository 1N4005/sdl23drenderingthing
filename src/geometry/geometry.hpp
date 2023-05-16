#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <vector>

namespace geo {
    struct Angle2 {
        float x_rot;
        float y_rot;

        Angle2(float x_rot, float y_rot);
    };

    struct Point2d {
        float x;
        float y;

        Point2d(float x, float y);
    };

    struct Point3d {
        float x;
        float y;
        float z;

        Point3d(float x, float y, float z);
    };

    struct Polygon2d {
        std::vector<Point2d> points;

        Polygon2d();
        Polygon2d(std::vector<Point2d> points);
    };

    struct Polygon3d {
        std::vector<Point3d> points;

        Polygon3d();
        Polygon3d(std::vector<Point3d> points);
    };

    struct Triangle2d : Polygon2d {
        Triangle2d(Point2d point1, Point2d point2, Point2d point3);
    };

    struct Triangle3d : Polygon3d {
        Triangle3d(Point3d point1, Point3d point2, Point3d point3);
    };

    struct Polyhedron3d {
        std::vector<Triangle3d> faces;

        Polyhedron3d();
        Polyhedron3d(std::vector<Triangle3d> faces);
    };
}

#endif
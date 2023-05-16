#ifndef UTILS_HPP
#define UTILS_HPP

#include <SDL2/SDL.h>
#include <vector>

#include "../geometry/geometry.hpp"

namespace utils {
    geo::Polygon2d convert_all_points(geo::Polygon3d poly, float fov, geo::Point3d camera, float x_rot, float y_rot, float z_rot, int width, int height);

    std::vector<geo::Polygon2d> convert_polyhedron_points(geo::Polyhedron3d poly, float fov, geo::Point3d camera, float x_rot, float y_rot, float z_rot, int width, int height);

    float to_radians(float degrees);
    float to_degrees(float radians);

    void draw_wireframe_polygon(SDL_Renderer* renderer, geo::Polygon2d poly);

    geo::Angle2 find_angleR(geo::Point3d center, geo::Point3d ray);

    geo::Point2d convert_point(geo::Point3d point, float hfov_radians, geo::Point3d camera, float x_rot, float y_rot, float z_rot, int width, int height);
}

#endif
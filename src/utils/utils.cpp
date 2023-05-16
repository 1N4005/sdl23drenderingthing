#include "utils.hpp"
#include "../geometry/geometry.hpp"

#include <SDL2/SDL.h>
#include <cstdio>
#include <iterator>

void utils::draw_wireframe_polygon(SDL_Renderer* renderer, geo::Polygon2d poly) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    float prev_x = poly.points[0].x;
    float prev_y = poly.points[0].y;
    SDL_RenderDrawLineF(renderer, prev_x, prev_y, poly.points[poly.points.size() - 1].x, poly.points[poly.points.size() - 1].y);
    for(int i=1; i<poly.points.size(); i++) {
        SDL_RenderDrawLineF(renderer, prev_x, prev_y, poly.points[i].x, poly.points[i].y);
        
        prev_x = poly.points[i].x;
        prev_y = poly.points[i].y;
    }
}

float utils::to_radians(float degrees) {
    return (M_PI * degrees) / 180;
}

float utils::to_degrees(float radians) {
    return (180 * radians) / M_PI;
}
//converts worldspace to screenspace
//all done in radians
geo::Point2d utils::convert_point(geo::Point3d point, float hfov_radians, geo::Point3d camera, float x_rot, float y_rot, float z_rot, int width, int height) {
    float vfov_radians = ((float) height / (float) width) * hfov_radians;

    float screen_x = point.x;
    float screen_y = point.z;

    auto [x, y] = find_angleR(camera, point);

    float relative_x_rot = x - x_rot;
    float relative_y_rot = y - y_rot;

    float x_portion = sqrt(pow(point.x - camera.x, 2) + pow(point.y - camera.y, 2)) * sin(relative_x_rot);
    float y_portion = sqrt(pow(point.y - camera.y, 2) + pow(point.z - camera.z, 2)) * sin(relative_y_rot);
    
    float perpendicular_distance;
    if(fmod(relative_x_rot, M_PI) != 0) {
        perpendicular_distance = x_portion / tan(relative_x_rot);
    } else {
        perpendicular_distance = sqrt(pow(point.x - camera.x, 2) + pow(point.y - camera.y, 2));
    }

    float total_x_portion = perpendicular_distance * tan(hfov_radians / 2);
   
    float total_y_portion = perpendicular_distance * tan(vfov_radians / 2);

    screen_x = width * (x_portion / total_x_portion);
    screen_y = height * (y_portion / total_y_portion);

    if(isnan(screen_x) || isnan(screen_y)) {
        screen_x = 0;
        screen_y = 0;
    }

    return geo::Point2d(screen_x + width / 2, height / 2 - screen_y);
}

geo::Angle2 utils::find_angleR(geo::Point3d center, geo::Point3d ray) {
    // rotation of (0, 0) means looking horizontal towards positive y
    float distance = sqrt(pow((ray.x - center.x), 2) + pow((ray.y - center.y), 2));
    float anglex_radians = atan((ray.x - center.x) / (ray.y - center.y));
    float angley_radians = atan((ray.z - center.z) / distance);

    geo::Angle2 angle(anglex_radians, angley_radians);

    return angle;
}

geo::Polygon2d utils::convert_all_points(geo::Polygon3d poly, float fov, geo::Point3d camera, float x_rot, float y_rot, float z_rot, int width, int height) {
    geo::Polygon2d new_poly;

    for(geo::Point3d point : poly.points) {
        new_poly.points.push_back(convert_point(point, fov, camera, x_rot, y_rot, z_rot, width, height));
    }

    return new_poly;
}

std::vector<geo::Polygon2d> utils::convert_polyhedron_points(geo::Polyhedron3d poly, float fov, geo::Point3d camera, float x_rot, float y_rot, float z_rot, int width, int height) {
    std::vector<geo::Polygon2d> faces;

    for(geo::Triangle3d face : poly.faces) {
        faces.push_back(convert_all_points(face, fov, camera, x_rot, y_rot, z_rot, width, height));
    }

    return faces;
}

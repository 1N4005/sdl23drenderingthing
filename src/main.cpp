#include <SDL2/SDL.h>

#include "geometry/geometry.hpp"
#include "utils/utils.hpp"

#include <chrono>
#include <cmath>

const int WIDTH = 600;
const int HEIGHT = 400;

const int FPS = 60;

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("3d", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    geo::Point3d camera(0, -300, 0);

    geo::Polyhedron3d octahedron;
    octahedron.faces.push_back(geo::Triangle3d(geo::Point3d(100, 0, 0), geo::Point3d(0, 100, 0), geo::Point3d(0, 0, 100)));
    octahedron.faces.push_back(geo::Triangle3d(geo::Point3d(100, 0, 0), geo::Point3d(0, -100, 0), geo::Point3d(0, 0, 100)));
    octahedron.faces.push_back(geo::Triangle3d(geo::Point3d(100, 0, 0), geo::Point3d(0, 100, 0), geo::Point3d(0, 0, -100)));
    octahedron.faces.push_back(geo::Triangle3d(geo::Point3d(100, 0, 0), geo::Point3d(0, -100, 0), geo::Point3d(0, 0, -100)));
    octahedron.faces.push_back(geo::Triangle3d(geo::Point3d(-100, 0, 0), geo::Point3d(0, 100, 0), geo::Point3d(0, 0, 100)));
    octahedron.faces.push_back(geo::Triangle3d(geo::Point3d(-100, 0, 0), geo::Point3d(0, 100, 0), geo::Point3d(0, 0, -100)));
    octahedron.faces.push_back(geo::Triangle3d(geo::Point3d(-100, 0, 0), geo::Point3d(0, -100, 0), geo::Point3d(0, 0, -100)));
    octahedron.faces.push_back(geo::Triangle3d(geo::Point3d(-100, 0, 0), geo::Point3d(0, -100, 0), geo::Point3d(0, 0, 100)));

    SDL_Rect bg;
    bg.x = 0;
    bg.y = 0;
    bg.w = WIDTH;
    bg.h = HEIGHT;

    float z_rot = 0;
    float x_rot = 0;
    float y_rot = 0;

    bool run = true;
    while(run) {
        auto start = std::chrono::high_resolution_clock::now();
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                run = false;
            }
        }
        const Uint8* keys = SDL_GetKeyboardState(NULL);
        if(keys[SDL_SCANCODE_W]) {
            camera.y += 2 * cos(utils::to_radians(x_rot));
            camera.x += 2 * sin(utils::to_radians(x_rot));
        } else if(keys[SDL_SCANCODE_S]) {
            camera.y -= 2 * cos(utils::to_radians(x_rot));
            camera.x -= 2 * sin(utils::to_radians(x_rot));
        }

        if(keys[SDL_SCANCODE_A]) {
            camera.y -= 2 * sin(utils::to_radians(x_rot));
            camera.x -= 2 * cos(utils::to_radians(x_rot));
        } else if(keys[SDL_SCANCODE_D]) {
            camera.y += 2 * sin(utils::to_radians(x_rot));
            camera.x += 2 * cos(utils::to_radians(x_rot));
        }

        if(keys[SDL_SCANCODE_SPACE]) {
            camera.z++;
        } else if(keys[SDL_SCANCODE_LSHIFT]) {
            camera.z--;
        }

        if(keys[SDL_SCANCODE_LEFT]) {
            x_rot--;
        } else if(keys[SDL_SCANCODE_RIGHT]) {
            x_rot++;
        } else if(keys[SDL_SCANCODE_UP]) {
            y_rot++;
        } else if(keys[SDL_SCANCODE_DOWN]) {
            y_rot--;
        }

        // printf("x: %f y: %f z: %f\nrot:\nx: %f y: %f z: %f\n\n", camera.x, camera.y, camera.z, utils::to_radians(x_rot), utils::to_radians(y_rot), utils::to_radians(z_rot));

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &bg);
        for(geo::Polygon2d poly : utils::convert_polyhedron_points(octahedron, utils::to_radians(60), camera, utils::to_radians(x_rot), utils::to_radians(y_rot), utils::to_radians(z_rot), WIDTH, HEIGHT)) {
            utils::draw_wireframe_polygon(renderer, poly);
        }
        SDL_RenderPresent(renderer);
        auto end = std::chrono::high_resolution_clock::now();
        long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        printf("%ld ms\n", elapsed);
        if(1000 / FPS > elapsed) {
            SDL_Delay(1000 / FPS - elapsed);
        }
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}
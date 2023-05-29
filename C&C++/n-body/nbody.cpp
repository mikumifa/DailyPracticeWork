// System Headers
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>
#include <omp.h>
// Project Headers
#include "nbody.h"

// #define GRAPHICS
#ifdef GRAPHICS
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#endif

// Number of particles
// #define SMALL
#define LARGE

#if defined(SMALL)
const int N = 1000;
#elif defined(LARGE)
const int N = 5000;
#endif

// Constants
const double min2 = 2.0;
const double G = 1 * 10e-10;
const double dt = 0.05;
const int NO_STEPS = 1000;

// Size of Window/Output image
const int width = 1920;
const int height = 1080;

// Bodies
std::vector<body> bodies(N);

// Define the number of threads to use
const int numThreads = std::thread::hardware_concurrency() ;
std::vector<std::vector<vec2>> sumArray(N,std::vector<vec2>(numThreads));
void updateBodyAcceleration(std::vector<body>& bodies, std::vector<vec2>& acc, int start, int end, double min2,int threads_No) {
    for (int i = start; i < end; ++i) {
        for (int j = i + 1; j < bodies.size(); ++j) {
            vec2 dx = bodies[i].pos - bodies[j].pos;
            vec2 u = normalise(dx);
            double d2 = length2(dx);

            if (d2 > min2) {
                double f = -G * bodies[i].mass * bodies[j].mass / d2;
                sumArray[j][threads_No] += (u * f / bodies[j].mass);
                acc[i] += (u * f / bodies[i].mass);
            }
        }
    }
}


void updateBodyPositionVelocity(std::vector<body>& bodies, std::vector<vec2>& acc, double dt, int start, int end) {
    for (int i = start; i < end; ++i) {
        bodies[i].pos += bodies[i].vel * dt;
        bodies[i].vel += acc[i] * dt;
    }
}

void update() {
    // Acceleration
    std::vector<vec2> acc(N, vec2(0, 0));

    // Divide the bodies among threads
    std::vector<std::thread> threads;
    int chunkSize = N / numThreads;
    int start = 0;
    int end = 0;

    // Calculate acceleration in parallel
    for (int i = 0; i < numThreads; ++i) {
        start = i * chunkSize;
        end = (i == numThreads - 1) ? N : (start + chunkSize);
        threads.emplace_back(updateBodyAcceleration, std::ref(bodies), std::ref(acc), start, end, min2,i+0);
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }
    threads.clear();
    for(int i = 0; i < N;i++) {
        for(int k=0;k<numThreads;k++) {
            acc[i]-=sumArray[i][k];
            sumArray[i][k]=vec2(0,0);
        }
    }
    threads.clear();
    for (int i = 0; i < numThreads; ++i) {
        start = i * chunkSize;
        end = (i == numThreads - 1) ? N : (start + chunkSize);
        threads.emplace_back(updateBodyPositionVelocity, std::ref(bodies), std::ref(acc), dt, start, end);
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }
}
void initialise() {
    // Create a central heavy body (sun)
    bodies[0] = body(width / 2, height / 2, 0, 0, 1e13, 5);

    // For each other body
    for (int i = 1; i < N; ++i) {
        // Pick a random radius, angle and calculate velocity
        double r = (uniform() + 0.1) * height / 2;
        double theta = uniform() * 2 * M_PI;
        double v = (height) / r;

        // Create orbiting body
        bodies[i] = body(width / 2 + r * cos(theta), height / 2 + r * sin(theta), -sin(theta) * v, cos(theta) * v, 1e9, 1);
    }
}

#ifdef GRAPHICS
// Main Function - Graphical Display
int main() {
    // Create Window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;
    sf::RenderWindow window(sf::VideoMode(width, height), "NBody Simulator", sf::Style::Default, settings);

    // Initialise NBody Simulation
    initialise();

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Update NBody Simluation
        update();

        // Clear the window with black color
        window.clear(sf::Color::Black);

        // Render Objects
        for (int i = 0; i < N; ++i) {
            // Create Circle
            sf::CircleShape shape(bodies[i].radius);
            shape.setFillColor(sf::Color(255, 0, 0));
            shape.setPosition(bodies[i].pos.x, bodies[i].pos.y);

            // Draw Object
            window.draw(shape);
        }

        // Display Window
        window.display();
    }
}
#else
// Main Function - Benchmark
int main() {
    // Initialise NBody Simulation
    initialise();

    // Get start time
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

    // Run Simulation
    for (int i = 0; i < NO_STEPS; i++) {
        // Update NBody Simluation
        update();
    }

    // Get end time
    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

    // Generate output image
    unsigned char *image = new unsigned char[width * height * 3];
    memset(image, 0, width * height * 3);

    // For each body
    for (int i = 0; i < N; ++i) {
        // Get Position
        vec2 p = bodies[i].pos;

        // Check particle is within bounds
        if (p.x >= 0 && p.x < width && p.y >= 0 && p.y < height) {
            // Add a red dot at body
            image[((((int) p.y * width) + (int) p.x) * 3)] = 255;
        }
    }

    // Write position data
    write_data("output.dat", bodies, N);

    // Write PNG output
    write_image("output.png", bodies, N, width, height);

    // Time Taken
    std::cout << "Time Taken: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0 << std::endl;
}
#endif
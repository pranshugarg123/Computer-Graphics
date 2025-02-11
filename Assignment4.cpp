#include <GLUT/glut.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure for a point
struct Point {
    int x, y;
};

// Define a quadrilateral (4 vertices)
vector<Point> polygon = {
    {100, 200},
    {200, 300},
    {300, 200},
    {200, 100}
};

int ymin = 10000, ymax = -10000;

// Function to draw a pixel
void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Function to fill the polygon using the scan-line algorithm
void scanLineFill() {
    for (const auto& p : polygon) {
        ymin = min(ymin, p.y);
        ymax = max(ymax, p.y);
    }

    for (int y = ymin; y <= ymax; y++) {
        vector<int> intersections;

        for (size_t i = 0; i < polygon.size(); i++) {
            Point p1 = polygon[i];
            Point p2 = polygon[(i + 1) % polygon.size()]; // Next vertex

            if (p1.y == p2.y) continue; // Ignore horizontal edges

            if (y >= min(p1.y, p2.y) && y < max(p1.y, p2.y)) {
                float x_intersect = p1.x + (float)(y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
                intersections.push_back((int)x_intersect);
            }
        }

        sort(intersections.begin(), intersections.end()); // Sort intersection points

        // Fill pixels between pairs of intersections
        for (size_t i = 0; i < intersections.size(); i += 2) {
            for (int x = intersections[i]; x <= intersections[i + 1]; x++) {
                drawPixel(x, y);
            }
        }
    }
    glFlush();
}

// Function to display the polygon and fill it
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0); // White for polygon edges
    glBegin(GL_LINE_LOOP);
    for (const auto& p : polygon) {
        glVertex2i(p.x, p.y);
    }
    glEnd();

    glColor3f(1.0, 0.0, 0.0); // Red for filling
    scanLineFill();

    glFlush();
}

// Initialize OpenGL
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Scan Line Fill Algorithm - Quadrilateral");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}


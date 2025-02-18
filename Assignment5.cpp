#include <GLUT/glut.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

vector<Point> polygon = {{100, 100}, {200, 50}, {300, 100}, {250, 200}, {150, 200}}; // Define a polygon

// Function to find the intersections of a scan line with polygon edges
void scanLineFill() {
    int ymin = polygon[0].y, ymax = polygon[0].y;

    // Find min and max Y
    for (const auto& p : polygon) {
        ymin = min(ymin, p.y);
        ymax = max(ymax, p.y);
    }

    // Loop through each scan line (horizontal line)
    for (int y = ymin; y <= ymax; y++) {
        vector<int> intersections;

        // Find intersections with polygon edges
        for (size_t i = 0; i < polygon.size(); i++) {
            size_t next = (i + 1) % polygon.size();
            int x1 = polygon[i].x, y1 = polygon[i].y;
            int x2 = polygon[next].x, y2 = polygon[next].y;

            if (y1 == y2) continue;  // Ignore horizontal edges

            if ((y >= min(y1, y2)) && (y <= max(y1, y2))) {
                int x_intersection = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
                intersections.push_back(x_intersection);
            }
        }

        // Sort intersections from left to right
        sort(intersections.begin(), intersections.end());

        // Fill between pairs of intersections
        for (size_t i = 0; i < intersections.size(); i += 2) {
            if (i + 1 < intersections.size()) {
                glBegin(GL_LINES);
                glVertex2i(intersections[i], y);
                glVertex2i(intersections[i + 1], y);
                glEnd();
            }
        }
    }
}

// Function to display the filled polygon
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the polygon outline
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    for (const auto& p : polygon)
        glVertex2i(p.x, p.y);
    glEnd();

    // Fill the polygon using Scan Line Fill
    glColor3f(1.0, 0.0, 0.0);
    scanLineFill();

    glFlush();
}

// Function to set up OpenGL
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);  // Set coordinate system
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Scan Line Fill Algorithm (OpenGL)");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}


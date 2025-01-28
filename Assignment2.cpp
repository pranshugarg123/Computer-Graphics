#include <GLUT/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

// Function to draw a line using the DDA algorithm
void drawLineDDA(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = max(abs(dx), abs(dy));
    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    float x = x1;
    float y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2i(round(x), round(y)); // Plot the point
        x += xIncrement;
        y += yIncrement;
    }
    glEnd();
    glFlush();
}

// Function to draw a line using Bresenham's algorithm
void drawLineBresenham(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1; // Step direction for x
    int sy = (y1 < y2) ? 1 : -1; // Step direction for y
    int err = dx - dy;

    glBegin(GL_POINTS);
    while (true) {
        glVertex2i(x1, y1); // Plot the current point
        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
    glEnd();
    glFlush();
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw lines using both algorithms
    // Line 1: DDA
    drawLineDDA(50, 50, 400, 300);

    // Line 2: Bresenham
    drawLineBresenham(100, 400, 400, 100);
}

// Initialization function
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    glColor3f(1.0, 1.0, 1.0);         // Set drawing color to white
    glPointSize(2.0);                 // Set point size
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);       // Set the coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA and Bresenham Line Drawing");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}


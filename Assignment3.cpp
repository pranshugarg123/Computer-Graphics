#include <GLUT/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

// Function to plot symmetrical points for a circle
void plotCirclePoints(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);
    glEnd();
    glFlush();
}

// Midpoint Circle Drawing Algorithm
void drawCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int p = 1 - r;
    while (x <= y) {
        plotCirclePoints(xc, yc, x, y);
        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
    }
}

// Function to plot symmetrical points for an ellipse
void plotEllipsePoints(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glEnd();
    glFlush();
}

// Midpoint Ellipse Drawing Algorithm
void drawEllipse(int xc, int yc, int rx, int ry) {
    int x = 0, y = ry;
    float d1 = ry * ry - rx * rx * ry + 0.25 * rx * rx;
    int dx = 2 * ry * ry * x;
    int dy = 2 * rx * rx * y;
    
    while (dx < dy) {
        plotEllipsePoints(xc, yc, x, y);
        x++;
        dx += 2 * ry * ry;
        if (d1 < 0) {
            d1 += dx + ry * ry;
        } else {
            y--;
            dy -= 2 * rx * rx;
            d1 += dx - dy + ry * ry;
        }
    }
    
    float d2 = ry * ry * (x + 0.5) * (x + 0.5) + rx * rx * (y - 1) * (y - 1) - rx * rx * ry * ry;
    while (y >= 0) {
        plotEllipsePoints(xc, yc, x, y);
        y--;
        dy -= 2 * rx * rx;
        if (d2 > 0) {
            d2 += rx * rx - dy;
        } else {
            x++;
            dx += 2 * ry * ry;
            d2 += dx - dy + rx * rx;
        }
    }
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw a circle with center (250, 300) and radius 100
    drawCircle(250, 300, 100);
    
    // Draw an ellipse with center (250, 150) and radii (150, 80)
    drawEllipse(250, 150, 150, 80);
}

// Initialization function
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Midpoint Circle and Ellipse Drawing");
    
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}


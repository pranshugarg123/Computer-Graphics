#include <GLUT/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

// Structure for a point
struct Point {
    float x, y;
};

// Global variables
Point triangle[3] = {{-0.5f, -0.5f}, {0.5f, -0.5f}, {0.0f, 0.5f}};

// Function to reflect about x-axis
void reflectX() {
    for (int i = 0; i < 3; i++) {
        triangle[i].y = -triangle[i].y;
    }
}

// Function to reflect about y-axis
void reflectY() {
    for (int i = 0; i < 3; i++) {
        triangle[i].x = -triangle[i].x;
    }
}

// Function to reflect about the line y = x + 2
void reflectYXplus2() {
    for (int i = 0; i < 3; i++) {
        // Shift origin to make line y = x
        triangle[i].y -= 2;

        // Swap x and y (Reflection about y = x)
        float temp = triangle[i].x;
        triangle[i].x = triangle[i].y;
        triangle[i].y = temp;

        // Shift back
        triangle[i].y += 2;
    }
}

// Function to apply shear along the x-axis
void shearX(float shx) {
    for (int i = 0; i < 3; i++) {
        triangle[i].x += shx * triangle[i].y;
    }
}

// Function to apply shear along the y-axis
void shearY(float shy) {
    for (int i = 0; i < 3; i++) {
        triangle[i].y += shy * triangle[i].x;
    }
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++) {
        glVertex2f(triangle[i].x, triangle[i].y);
    }
    glEnd();

    glFlush();
}

// Keyboard input handler
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'x': reflectX(); break;
        case 'y': reflectY(); break;
        case 'l': reflectYXplus2(); break;
        case 'h': shearX(0.5); break;
        case 'v': shearY(0.5); break;
        case 'q': exit(0);
    }
    glutPostRedisplay();
}

// Initialization
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Reflection & Shearing");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}


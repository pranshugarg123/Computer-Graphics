#include <GLUT/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

// Structure for a point
struct Point {
    float x, y;
};

// Global Variables
Point triangle[3] = {{-0.5f, -0.5f}, {0.5f, -0.5f}, {0.0f, 0.5f}};
Point fixedPoint = {0.0f, 0.0f}; // Default transformation about origin

// Function to apply translation
void translate(float tx, float ty) {
    for (int i = 0; i < 3; i++) {
        triangle[i].x += tx;
        triangle[i].y += ty;
    }
}

// Function to apply scaling about origin
void scale(float sx, float sy) {
    for (int i = 0; i < 3; i++) {
        triangle[i].x *= sx;
        triangle[i].y *= sy;
    }
}

// Function to apply scaling about a fixed point
void scaleFixedPoint(float sx, float sy, Point fp) {
    for (int i = 0; i < 3; i++) {
        triangle[i].x = fp.x + (triangle[i].x - fp.x) * sx;
        triangle[i].y = fp.y + (triangle[i].y - fp.y) * sy;
    }
}

// Function to apply rotation about origin
void rotate(float angle) {
    float rad = angle * M_PI / 180.0; // Convert to radians
    for (int i = 0; i < 3; i++) {
        float x_new = triangle[i].x * cos(rad) - triangle[i].y * sin(rad);
        float y_new = triangle[i].x * sin(rad) + triangle[i].y * cos(rad);
        triangle[i].x = x_new;
        triangle[i].y = y_new;
    }
}

// Function to apply rotation about a fixed point
void rotateFixedPoint(float angle, Point fp) {
    translate(-fp.x, -fp.y); // Move to origin
    rotate(angle);
    translate(fp.x, fp.y); // Move back
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
        case 't': translate(0.1, 0.1); break;
        case 's': scale(1.2, 1.2); break;
        case 'S': scaleFixedPoint(1.2, 1.2, fixedPoint); break;
        case 'r': rotate(15); break;
        case 'R': rotateFixedPoint(15, fixedPoint); break;
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
    glutCreateWindow("2D Transformations");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}


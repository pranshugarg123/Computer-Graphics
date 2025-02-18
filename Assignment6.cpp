#include <GLUT/glut.h>

#include <iostream>

using namespace std;

const int WIDTH = 600, HEIGHT = 600;
float fillColor[3] = {1.0, 0.0, 0.0};  // Red
float boundaryColor[3] = {1.0, 1.0, 1.0};  // White

// Polygon definitions
float convexPolygon[][2] = {{100, 100}, {300, 50}, {400, 200}, {200, 300}, {100, 200}};
int convexVertices = 5;

float concavePolygon[][2] = {{450, 100}, {550, 150}, {500, 200}, {550, 250}, {450, 300}, {400, 200}};
int concaveVertices = 6;

// Get the color of a pixel
void getPixelColor(int x, int y, float color[3]) {
    glReadPixels(x, HEIGHT - y, 1, 1, GL_RGB, GL_FLOAT, color);
}

// Set the color of a pixel
void setPixel(int x, int y, float color[3]) {
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// **4-Connected Boundary Fill**
void boundaryFill4(int x, int y, float fillColor[3], float boundaryColor[3]) {
    float color[3];
    getPixelColor(x, y, color);

    if ((color[0] != boundaryColor[0] || color[1] != boundaryColor[1] || color[2] != boundaryColor[2]) &&
        (color[0] != fillColor[0] || color[1] != fillColor[1] || color[2] != fillColor[2])) {
        setPixel(x, y, fillColor);
        glutPostRedisplay();
        boundaryFill4(x + 1, y, fillColor, boundaryColor);
        boundaryFill4(x - 1, y, fillColor, boundaryColor);
        boundaryFill4(x, y + 1, fillColor, boundaryColor);
        boundaryFill4(x, y - 1, fillColor, boundaryColor);
    }
}

// Function to draw a polygon
void drawPolygon(float polygon[][2], int vertices) {
    glColor3f(boundaryColor[0], boundaryColor[1], boundaryColor[2]);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < vertices; i++) {
        glVertex2i(polygon[i][0], polygon[i][1]);
    }
    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw convex polygon
    drawPolygon(convexPolygon, convexVertices);
    boundaryFill4(200, 150, fillColor, boundaryColor);

    // Draw concave polygon
    drawPolygon(concavePolygon, concaveVertices);

    glFlush();
}

// Initialize OpenGL
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Boundary Fill & Flood Fill (OpenGL)");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}


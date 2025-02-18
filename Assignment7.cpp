#include <GLUT/glut.h>
#include <iostream>
#include <vector>

using namespace std;

// Window size
const int WIDTH = 800, HEIGHT = 600;

// List to store pixel activation
vector<pair<int, int>> pixelList;

// Function to set pixel and store activation
void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    pixelList.push_back({x, y}); // Store the activated pixel
}

// Function to draw a line
void drawLine(int x1, int y1, int x2, int y2) {
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
}

// Function to draw a rectangle
void drawRectangle(int x, int y, int width, int height) {
    glBegin(GL_LINE_LOOP);
    glVertex2i(x, y);
    glVertex2i(x + width, y);
    glVertex2i(x + width, y + height);
    glVertex2i(x, y + height);
    glEnd();
}

// Function to draw a circle (Bresenham’s Algorithm)
void drawCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;

    while (y >= x) {
        setPixel(xc + x, yc + y);
        setPixel(xc - x, yc + y);
        setPixel(xc + x, yc - y);
        setPixel(xc - x, yc - y);
        setPixel(xc + y, yc + x);
        setPixel(xc - y, yc + x);
        setPixel(xc + y, yc - x);
        setPixel(xc - y, yc - x);

        x++;
        if (d > 0) {
            y--;
            d += 4 * (x - y) + 10;
        } else {
            d += 4 * x + 6;
        }
    }
}

// Function to draw a house
void drawHouse() {
    // Main house body
    drawRectangle(100, 200, 200, 150);

    // Roof
    glBegin(GL_TRIANGLES);
    glVertex2i(100, 350);
    glVertex2i(300, 350);
    glVertex2i(200, 450);
    glEnd();

    // Door
    drawRectangle(180, 200, 40, 80);

    // Windows
    drawRectangle(120, 260, 40, 40);
    drawRectangle(240, 260, 40, 40);
}

// Function to draw a car
void drawCar() {
    // Car body
    drawRectangle(400, 200, 200, 80);

    // Roof
    glBegin(GL_POLYGON);
    glVertex2i(420, 280);
    glVertex2i(580, 280);
    glVertex2i(560, 320);
    glVertex2i(440, 320);
    glEnd();

    // Wheels
    drawCircle(440, 190, 20);
    drawCircle(560, 190, 20);
}

// Function to draw a fish
void drawFish() {
    // Fish body
    glBegin(GL_POLYGON);
    glVertex2i(100, 500);
    glVertex2i(180, 520);
    glVertex2i(250, 500);
    glVertex2i(180, 480);
    glEnd();

    // Tail
    glBegin(GL_TRIANGLES);
    glVertex2i(250, 500);
    glVertex2i(280, 520);
    glVertex2i(280, 480);
    glEnd();

    // Eye
    drawCircle(120, 510, 5);
}

// Function to draw a stick man
void drawMan() {
    // Head
    drawCircle(600, 400, 20);

    // Body
    drawLine(600, 380, 600, 320);

    // Arms
    drawLine(570, 350, 630, 350);

    // Legs
    drawLine(600, 320, 580, 280);
    drawLine(600, 320, 620, 280);
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawHouse();
    drawCar();
    drawFish();
    drawMan();

    glFlush();

    // Print activated pixels
    cout << "Pixel Activation List:\n";
    for (auto p : pixelList) {
        cout << "(" << p.first << ", " << p.second << ")\n";
    }
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
    glutCreateWindow("2D Objects - OpenGL");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

